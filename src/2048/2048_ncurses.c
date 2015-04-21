#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <grid.h>

#define NEW_GAME 1
#define TO_CLEAR 10

// structure qui contient les propriétés d'affichage de la box
typedef struct _box_border_struct {
	chtype ls, rs, ts, bs, tl, tr, bl, br;
}BOX_BORDER;


typedef struct _BOX_struct {
	int startx, starty;
	int height, width;
	BOX_BORDER border;
}BOX;

void init_win();
void init_box_params(BOX *p_box);
void create_boxes(BOX *box);
void update_boxes(BOX *box, grid g);
int end_game(grid g);
unsigned long int pow_of_2(tile t);

int main(int argc, char *argv[]) {	
	// initialisation de time pour la génération aléatoire de tile
	srand(time(NULL));
	
	BOX box;				// paramètre de la console
	int key;				// caractère saisi au clavier
	bool next_round;		// valeur boolean est à vrai quand on veut recommencer une partie
	dir direction;			// contient la direction décrite dans grid.h
	grid g;					// instance de la grid

	init_win();
	init_box_params(&box);
	create_boxes(&box);

	while(NEW_GAME){
		g=new_grid();
		add_tile(g);
		add_tile(g);
		update_boxes(&box, g);
		next_round=true;

		while(next_round)
		{
			key = getch();

			switch(key)
			{
				case KEY_DOWN:
					direction = DOWN;
					break;
				case KEY_UP:
					direction = UP;
					break;
				case KEY_RIGHT:
					direction = RIGHT;
					break;
				case KEY_LEFT:
					direction = LEFT;
					break;
				case 'q':
					return end_game(g);
				case 'r':
					next_round=false;
				default:
					continue;
			}

			// Vérification de la possibilité du mouvement
			if(!can_move(g, direction))
		 	{
		 		mvprintw(box.height * GRID_SIDE + 3, 0, "Erreur: mouvement impossible");
		 		continue;
		 	}

		 	// Réalisation du coup dans la direction voulue
		 	play(g, direction);
		 	// Rafraichissement de l'affichage
			update_boxes(&box, g);

			// dans le cas où la partie est terminée
			while (game_over(g) && next_round){
				mvprintw(box.height * GRID_SIDE + 3, 0, "voulez-vous rejouer ? : y , n");
				key = getch();
				mvprintw(box.height * GRID_SIDE + 4, 0, "%c", key);
				if (key=='y')
					next_round=false;
				
				if (key=='n'){
					return end_game(g);
				}
			}// fin game_over
		} // fin next_round
		delete_grid(g);
	} // fin PARTIE_SUIVANTE
	return end_game(g);
}

/*
 * initialise la fenêtre ncurses
 */
void init_win()
{
	initscr();				/* initialise le mode curses*/
	start_color();			/* initialise la fonctionalité de la couleur */
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(FALSE);		/* supprime le curseur */
	noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	refresh();
	attroff(COLOR_PAIR(1));
}

/*
 * initialise les propriétés des box
 */
void init_box_params(BOX *p_box)
{
	p_box->height = 2;
	p_box->width = 10;
	p_box->starty = 0;	
	p_box->startx = 0;

	p_box->border.ls = '|';
	p_box->border.rs = '|';
	p_box->border.ts = '-';
	p_box->border.bs = '-';
	p_box->border.tl = '+';
	p_box->border.tr = '+';
	p_box->border.bl = '+';
	p_box->border.br = '+';

}

/*
 * \Créé la grille dans la fenêtre et tous les utilitaires d'arrière-plan
 * \paramètre p_box les propriétés des box de ncurses
 */
void create_boxes(BOX *p_box)
{
	int x, y, w, h;

	x = p_box->startx;
	y = p_box->starty;
	w = p_box->width;
	h = p_box->height;

	// créé une grille vide dans la fenêtre
	for (int i = 0; i < GRID_SIDE; i++)
	{
		for (int j = 0; j < GRID_SIDE; j++)
		{
			mvaddch(y + h*j, x + w*i, p_box->border.tl);			// dessine le coin supérieur gauche d'une box
			mvaddch(y + h*j, x + w*(i+1), p_box->border.tr);		// dessine le coin supérieur droit d'une box
			mvaddch(y + h*(j+1), x + w*i, p_box->border.bl);		// dessine le coin inférieur gauche d'une box
			mvaddch(y + h*(j+1), x + w*(i+1), p_box->border.br);	// dessine le coin inférieur droit d'une box

			mvhline(y + h*j, x+1 + w*i, p_box->border.ts, w-1);		// dessine le trait supérieur
			mvhline(y + h*(j+1), x+1 + w*i, p_box->border.bs, w-1);	// dessine le trait inférieur
			mvvline(y+1 + h*j, x + w*i, p_box->border.ls, h-1);		// dessine le trait gauche
			mvvline(y+1 + h*j, x + w*(i+1), p_box->border.rs, h-1);	// dessine le trait droit
		}
	}

	mvprintw(h * GRID_SIDE + 1, 0, "score: ");
	mvprintw(h * GRID_SIDE + 2, 0, "Direction : fleches    Restart : r    Quit : q");

	refresh();
}


/*
 * \Met à jour le contenu de la grille affiché dans la fenêtre et supprime l'aide pour les utilisateurs
 * \paramètre p_box les porpriétés des box de ncurses
 * \param g the grid
 */
void update_boxes(BOX *p_box, grid g)
{
	int x, y, w, h;

	x = p_box->startx;
	y = p_box->starty;
	w = p_box->width;
	h = p_box->height;

	// Efface le contenu de chaque tuile et les remplace par leur nouvelle valeur
	for (int j= 0; j< GRID_SIDE;j++)
	{
		for (int i = 0; i < GRID_SIDE; i++)
		{
			mvhline(y + h * j + 1, x + w * i + 1, ' ', w - 2);

			if(get_tile(g, j, i) != 0)
				mvprintw(y + h * j + 1, x + w * i + 1, "%lu", pow_of_2(get_tile(g, j, i)));

			if(get_tile(g, j, i) >= 11)
				mvprintw(h * GRID_SIDE / 2, w * GRID_SIDE + 3,  "Bravo ! vous avez atteint 2048");
		}
	}

	// Efface tout ce qui apparait sous la grille sauf la ligne 2 et le début de la ligne 1
	for (int i = 1; i < TO_CLEAR; i++)
	{
		if(i == 1)
			mvhline(h * GRID_SIDE + i, 8, ' ', w * GRID_SIDE);
		else if(i != 2)
			mvhline(h * GRID_SIDE + i, 0, ' ', w * GRID_SIDE);
	}

	// met à jour le score
	mvprintw(h * GRID_SIDE + 1, 8, "%lu", grid_score(g));
	refresh();
}

/*
 * \ferme la fenêtre créée par ncurses & supprimes la grille
 * \paramètre g, la grille
 */
int end_game(grid g)
{
	endwin();
	printf("Merci d'avoir joue.\n");
	delete_grid(g);
	return EXIT_SUCCESS;
}


unsigned long int pow_of_2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

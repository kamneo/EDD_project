#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <strategy.h>
#include <unistd.h>
#include <grid.h>

#define NOUVELLE_PARTIE 1
#define TO_CLEAR 10
#define MAX_VALUE 11

// struct which contains diplay properties of the box
typedef struct _box_border_struct {
	chtype ls, rs, ts, bs, tl, tr, bl, br;
} BOX_BORDER;

// struct which contains all diplay properties of the box
typedef struct _BOX_struct {
	int startx, starty;
	int height, width;
	BOX_BORDER border;
} BOX;

/*
 * MEMOIRE qui contient les scores cumulés des grilles jusqu'a ce que
 * l'utilisateur quitte le programme et le nombre de fois que la valeur max
 * est apparue
 */
typedef struct _memoire {
	int* tab;
	unsigned long int score;
} MEMOIRE;

void init_win();
void init_box_params(BOX *p_box);
void create_boxes(BOX *box);
void update_boxes(BOX *box, grid g);
int end_game(grid g);
int end_game_stat(MEMOIRE m, grid g);
unsigned long int pow_of_2(tile t);

int main(int argc, char *argv[]) {
	// initialisation de time pour la génération aléatoire de tile
	srand(time(NULL));

	MEMOIRE m;
	m.score = 0;
	m.tab = malloc(sizeof(int) * MAX_VALUE);

	strategy strat = malloc(sizeof(struct strategy_s)); //initialisation de notre structure strategy
	strat->name = "Coins";						// Nom de la strategie
	strat->play_move = strategie_coin_1; 		//cf strategy.c
	strat->mem = malloc(sizeof(int));
	*(int*) (strat->mem) = 0; // on pointe sur un int qui sera un compteur de tour jouer(pour certaine strat)
	strat->free_strategy = NULL;

	BOX box;				// parametre de la console
	int key;				// caractere saisi au clavier
	bool tour_suivant;// valeur boolean est a vrai quand on veut recommencer une partie
	dir direction;			// contient la direction décrite dans grid.h
	grid g;					// instance de la grid

	init_win();
	init_box_params(&box);
	create_boxes(&box);

	while (NOUVELLE_PARTIE) {
		g = new_grid();
		add_tile(g);
		add_tile(g);
		update_boxes(&box, g);
		tour_suivant = true;

		while (tour_suivant) {
			direction = strat->play_move(strat, g);

			// Réalisation du coup dans la direction voulue
			play(g, direction);
			// Rafraichissement de l'affichage
			update_boxes(&box, g);

			// dans le cas ou la partie est terminée
			while (game_over(g) && tour_suivant) {
				// Ceci ne sert que pour les stats
				m.score += grid_score(g);
				int indice = 0;
				for (int x = 0; x < GRID_SIDE; ++x) {
					for (int y = 0; y < GRID_SIDE; ++y) {
						if (get_tile(g, x, y) > indice) {
							indice = get_tile(g, x, y);
						}
					}
				}
				m.tab[indice] += 1;

				mvprintw(box.height * GRID_SIDE + 3, 0,
						"voulez-vous rejouer ? : y , n");
				key = getch();
				mvprintw(box.height * GRID_SIDE + 4, 0, "%c", key);
				if (key == 'y')
					tour_suivant = false;

				if (key == 'n') {
					return end_game_stat(m, g);
				}
			}					// end game_over
		} // end tour_suivant
	} // end PARTIE_SUIVANTE
	return end_game(g);
}

/*
 * brief initialize the ncurses windows
 */
void init_win() {
	initscr(); /* Start curses mode 		*/
	start_color(); /* Start the color functionality */
	cbreak();
	keypad(stdscr, TRUE); /* I need that nifty F1 	*/
	curs_set(FALSE); /* disable cursor */
	noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	refresh();
	attroff(COLOR_PAIR(1));
}

/*
 * brief initialize boxes proprieties
 */
void init_box_params(BOX *p_box) {
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
 * \brief create the grid on windows and all backgroud utilities
 * \param p_box the boxes properties of ncurses
 */
void create_boxes(BOX *p_box) {
	int x, y, w, h;

	x = p_box->startx;
	y = p_box->starty;
	w = p_box->width;
	h = p_box->height;

	// create an empty grid in the window
	for (int i = 0; i < GRID_SIDE; i++) {
		for (int j = 0; j < GRID_SIDE; j++) {
			mvaddch(y + h * j, x + w * i, p_box->border.tl); // draw the left up corner of a box
			mvaddch(y + h * j, x + w * (i + 1), p_box->border.tr); // draw the right up corner of a box
			mvaddch(y + h * (j + 1), x + w * i, p_box->border.bl); // draw the left down corner of a box
			mvaddch(y + h * (j + 1), x + w * (i + 1), p_box->border.br); // draw the right down corner of a box

			mvhline(y + h * j, x + 1 + w * i, p_box->border.ts, w - 1);	// draw the up corner of a box
			mvhline(y + h * (j + 1), x + 1 + w * i, p_box->border.bs, w - 1);// draw the down corner of a box
			mvvline(y + 1 + h * j, x + w * i, p_box->border.ls, h - 1);	// draw the left corner of a box
			mvvline(y + 1 + h * j, x + w * (i + 1), p_box->border.rs, h - 1);// draw the right corner of a box
		}
	}

	mvprintw(h * GRID_SIDE + 1, 0, "score: ");

	refresh();
}

/*
 * \brief update the content of the grid display in window and delete help for users
 * \param p_box the boxes properties of ncurses
 * \param g the grid
 */
void update_boxes(BOX *p_box, grid g) {
	int x, y, w, h;

	x = p_box->startx;
	y = p_box->starty;
	w = p_box->width;
	h = p_box->height;

	// Efface le contenu de chaque tile et les remplace par leur nouvelle valeur
	for (int j = 0; j < GRID_SIDE; j++) {
		for (int i = 0; i < GRID_SIDE; i++) {
			mvhline(y + h * j + 1, x + w * i + 1, ' ', w - 2);

			if (get_tile(g, j, i) != 0)
				mvprintw(y + h * j + 1, x + w * i + 1, "%lu",
						pow_of_2(get_tile(g, j, i)));

			if (get_tile(g, j, i) >= 11)
				mvprintw(h * GRID_SIDE / 2, w * GRID_SIDE + 3,
						"Bravo ! vous avez atteint 2048");
		}
	}

	// Efface tout ce qui apparait sous la grille sauf la ligne 2 et le debut de la ligne 1
	for (int i = 1; i < TO_CLEAR; i++) {
		if (i == 1)
			mvhline(h * GRID_SIDE + i, 8, ' ', w * GRID_SIDE);
		else if (i != 2)
			mvhline(h * GRID_SIDE + i, 0, ' ', w * GRID_SIDE);
	}

	// met a jour le score
	mvprintw(h * GRID_SIDE + 1, 8, "%lu", grid_score(g));
	refresh();
}

/*
 * \brief close the window created by ncurses & delete the grid
 * \param g the grid
 */
int end_game(grid g) {
	endwin();
	printf("Merci d'avoir joue.\n");
	delete_grid(g);
	return EXIT_SUCCESS;
}

/*
 * \brief close the window created by ncurses & delete the grid & display the statistics
 * \param g the grid
 * \param m Memoire
 */
int end_game_stat(MEMOIRE m, grid g) {
	endwin();
	printf("Merci d'avoir joue.\n");
	delete_grid(g);
	printf("%lu \n", m.score);
	for (int i = 0; i < MAX_VALUE; ++i) {
		printf("%f = %d\n", pow(2, i), m.tab[i]);
	}

	free(m.tab);
	return EXIT_SUCCESS;
}

/*
 * \brief Calculate the pow of the tile
 * \param t the tile to be calculate
 * \return the pow of the tile if t > 0 or return 0
 */
unsigned long int pow_of_2(tile t) {
	if (t == 0)
		return t;
	return pow(2, t);
}

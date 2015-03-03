#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include "grid.h"

#define NOUVELLE_PARTIE 1

typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

	int startx, starty;
	int height, width;
	WIN_BORDER border;
}WIN;

void init_win_params(WIN *p_win);
void create_box(WIN *win);
void update_box(WIN *win, grid g);
unsigned long int pow_of_2(tile t);

int main(int argc, char *argv[])
{	
	WIN win;
	int ch, key;
	bool tour_suivant;
	dir direction;
	grid g;

	initscr();			/* Start curses mode 		*/
	start_color();			/* Start the color functionality */
	cbreak();			
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	curs_set(FALSE);		/* disable cursor */
	noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	/* Initialize the window parameters */
	init_win_params(&win);

	attron(COLOR_PAIR(1));
	refresh();
	attroff(COLOR_PAIR(1));
	
	create_box(&win);

	while(NOUVELLE_PARTIE){

		g=new_grid();
		add_tile(g);
		add_tile(g);
		update_box(&win, g);
		tour_suivant=true;

		while(tour_suivant){
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
					endwin();			/* End curses mode		  */
					printf("Merci d'avoir joue.\n");
					exit(0);
				default:
					continue;
			}

			if(!can_move(g, direction))
		 	{
		 		mvprintw(win.height * GRID_SIDE + 3, 0, "Erreur: mouvement impossible");
		 		continue;
		 	}

		 	play(g, direction);
			update_box(&win, g);

			while (game_over(g) && tour_suivant){
				mvprintw(win.height * GRID_SIDE + 3, 0, "voulez vous rejouer : y , n");
				key = getch();
				mvprintw(win.height * GRID_SIDE + 4, 0, "%c", key);
				if (key=='y')
					tour_suivant=false;
				
				if (key=='n'){
					endwin();			/* End curses mode		  */
					printf("Merci d'avoir joue.\n");
					return 0;
				}
			}		
				
		}
	}

	getch();
	endwin();			/* End curses mode		  */
	return 0;
}

void init_win_params(WIN *p_win)
{
	p_win->height = 2;
	p_win->width = 10;
	p_win->starty = 0;	
	p_win->startx = 0;

	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';

}

void create_box(WIN *p_win)
{
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	for (int i = 0; i < GRID_SIDE; i++)
	{
		for (int j = 0; j < GRID_SIDE; j++)
		{
			mvaddch(y + h * j, x + w * i, p_win->border.tl);
			mvaddch(y + h * j, x + w * (i + 1), p_win->border.tr);
			mvaddch(y + h * (j + 1), x + w * i, p_win->border.bl);
			mvaddch(y + h * (j + 1), x + w * (i + 1), p_win->border.br);

			mvhline(y + h * j, x + 1 + w * i, p_win->border.ts, w - 1);
			mvhline(y + h * (j + 1), x + 1 + w * i, p_win->border.bs, w - 1);
			mvvline(y + 1 + h * j, x + w * i, p_win->border.ls, h - 1);
			mvvline(y + 1 + h * j, x + w * (i + 1), p_win->border.rs, h - 1);
		}
	}

	mvprintw(h * GRID_SIDE + 1, 0, "score: ");
	mvprintw(h * GRID_SIDE + 2, 0, "Direction : fleches    Restart : r    undo : u    Quit : q");
				
	refresh();
}

void update_box(WIN *p_win, grid g)
{
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	for (int j= 0; j< GRID_SIDE;j++)
	{
		for (int i = 0; i < GRID_SIDE; i++)
		{
			mvhline(y + h * j + 1, x + w * i + 1, ' ', w - 2);

			if(get_tile(g, j, i) != 0)
				mvprintw(y + h * j + 1, x + w * i + 1, "%lu", pow_of_2(get_tile(g, j, i)));

		}
	}
	mvhline(h * GRID_SIDE + 1, 8, ' ', w * GRID_SIDE);
	mvprintw(h * GRID_SIDE + 1, 8, "%lu", grid_score(g));

	mvhline(h * GRID_SIDE + 3, 0, ' ', w * GRID_SIDE);

	refresh();
}

/*
 * \brief Calculate the pow of the tile
 * \param t the tile to be calculate
 * \return the pow of the tile if t > 0 or return 0
 */
unsigned long int pow_of_2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}
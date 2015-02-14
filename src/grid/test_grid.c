/*
 * Fichier de test du module grid
 */
#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include <math.h>

static unsigned long int puissanceDe2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

static void display_grid(grid g)
{

	for(int i = 0; i < GRID_SIDE * 2 +1; i++)
    {
	    if(i % 2 == 0)
	    	if (i != 0)
	    		printf("|\n+");
	    	else
	    		printf("+");
	    else
	    	printf("\n");

	    for(int j = 0; j < GRID_SIDE; j++)
	    	if(i % 2 != 0)
	    	{
	    		unsigned long int s = puissanceDe2(get_tile(g, i/2, j));
	        	printf("| %lu \t", s);
	        }
	        else {
	        	printf("-------+");
	        }
    }

	printf("\n le score est de : %lu \n\n",grid_score(g));
}

int main (int arc, char** argv)
{
	grid g;
	g = new_grid ();

	printf("affichage de la grille lors de la création ! \n");
	display_grid(g);

	printf("le résultat de la grille est : %lu\n", grid_score(g));
	
	printf("modification de la grille \n");
	set_tile (g, 0, 0, 2);
	set_tile (g, 0, 2, 4);
	set_tile (g, 0, 3, 4);
	set_tile (g, 0, 1, 2);
	display_grid(g);
	printf("le résultat de la grille est : %lu\n", grid_score(g));

	printf("la grille peut %s bouger vers le haut !\n", can_move(g, UP)? "" : "pas");

	printf("la grille peut %s bouger vers le bas !\n", can_move(g, DOWN)? "" : "pas");

	printf("la grille peut %s bouger vers la droite!\n", can_move(g, RIGHT)? "" : "pas");

	printf("la grille peut %s bouger vers la gauche!\n", can_move(g, LEFT)? "" : "pas");
	do_move(g, RIGHT);
	display_grid(g);
	do_move(g, RIGHT);
	display_grid(g);
	do_move(g, LEFT);
	display_grid(g);

	add_tile(g);
	display_grid(g);
	return EXIT_SUCCESS;
}


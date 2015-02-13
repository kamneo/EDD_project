/*
 * Fichier de test du module grid
 */
#include <stdlib.h>
#include <stdio.h>
#include "grid.h"


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
	        	printf("| %d \t", get_tile(g, i/2, j));
	        else {
	        	printf("-------+");
	        }
    }

	printf("\n");
}


int main (int arc, char** argv)
{
	grid g;
	g = new_grid ();

	printf("affichage de la grille lors de la création ! \n");
	display_grid(g);

	printf("le résultat de la grille est : %lu\n", grid_score(g));
	
	printf("modification de la grille \n");
	set_tile (g, 0, 0, 1);
	display_grid(g);
	printf("le résultat de la grille est : %lu\n", grid_score(g));

	printf("la grille peut %s bouger !\n", can_move(g, UP)? "" : "pas");


	return EXIT_SUCCESS;
}


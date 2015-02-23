/*
 * Fichier de test du module grid
 * Affiche la grille apres un mouvement
 */
#include <stdlib.h>
#include <stdio.h>

#include "grid.h"
#include "affichage.h"

int main (int arc, char** argv)
{
	grid g;
	g = new_grid ();

	for(int i = 0; i < GRID_SIDE; i++){
		for (int j = 0; j < GRID_SIDE; j++)
		{
			if((i+j)%2 == 0)
				set_tile(g, i, j, i+j);
		}
	}
	
	printf("%s\n", game_over(g)? "1" : "0");

	set_tile(g, 0, 0, 10)
	
	printf("%s\n", game_over(g)? "1" : "0");

	return EXIT_SUCCESS;
}
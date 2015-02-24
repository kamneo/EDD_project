/*
 * Fichier de test du module grid
 * Affiche la grille après la copy d'une grille dans l'autre
 */
#include <stdlib.h>
#include <stdio.h>

#include "grid.h"
#include "affichage.h"
#include "utilities.h"

 int main (int arc, char** argv){
 	grid g1, g2;
	g1 = new_grid ();
	g2 = new_grid ();

	add_tile (g1);
	add_tile (g1);
	add_tile (g1);
	add_tile (g1);

	copy_grid(g1, g2);

	for(int i = 0; i < GRID_SIDE; i++){
		for (int j = 0; j < GRID_SIDE; j++)
		{
			if(get_tile(g1, i, j) != get_tile(g2, i, j))
				printf("%d\n", 1);
			else
				printf("%d\n", 0);
		}
	}

	return EXIT_SUCCESS;
 }
/*
 * Fichier de test du module grid - test new grid
 * Affiche la grille après l'ajout d'une tile aléatoire et set_tile
 */
#include <stdlib.h>
#include <stdio.h>

#include <grid.h>

int main (int argc, char** argv){
 	grid g;
	g = new_grid ();

	for (int i = 0; i < GRID_SIDE; i++){
		for (int j = 0; j < GRID_SIDE; j++){
			if(get_tile(g, i, j) != 0)
			{
				delete_grid(g);
				return EXIT_FAILURE;
			}
		}
	}

	delete_grid(g);
	printf("test ok !\n");
	return EXIT_SUCCESS;
}

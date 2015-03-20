/*
 * Fichier de test du module grid - test copy_grid()
 * Test si les grilles sont les mêmes après la copy d'une grille dans l'autre
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <grid.h>

int main (int argc, char** argv){
 	srand(time(NULL));
 	
 	grid g1, g2;
	g1 = new_grid ();
	g2 = new_grid ();

	add_tile (g1);
	add_tile (g1);
	add_tile (g1);
	add_tile (g1);

	copy_grid(g1, g2);

	// Vérification du score
	if(grid_score(g1) != grid_score(g2)){
		delete_grid(g1);
		delete_grid(g2);

		return EXIT_FAILURE;
	}

	// vérification case à case
	for(int i = 0; i < GRID_SIDE; i++){
		for (int j = 0; j < GRID_SIDE; j++)
		{
			if(get_tile(g1, i, j) != get_tile(g2, i, j)){
				delete_grid(g1);
				delete_grid(g2);

				return EXIT_FAILURE;
			}

		}
	}

	add_tile(g2);
	bool test_ok = false;
	// vérification case à case
	for(int i = 0; i < GRID_SIDE; i++){
		for (int j = 0; j < GRID_SIDE; j++)
		{
			if(get_tile(g1, i, j) != get_tile(g2, i, j)){
				test_ok = true;
			}

		}
	}

	if(!test_ok){
		delete_grid(g1);
		delete_grid(g2);

		return EXIT_FAILURE;
	}

	delete_grid(g1);
	delete_grid(g2);

	return EXIT_SUCCESS;
}

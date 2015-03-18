/*
 * Fichier de test du module grid - test_game_over()
 * Affiche si la partie est terminée ou non
 */
#include <stdlib.h>
#include <stdio.h>

#include <grid.h>
#include <affichage.h>

int main (int argc, char** argv)
{
	grid g;
	g = new_grid ();
	bool test_ok = true;

	for(int i = 0; i < GRID_SIDE; i++){
		for (int j = 0; j < GRID_SIDE; j++)
		{
			set_tile(g, i, j, i+j);
		}
	}
	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		| 0| 1| 2| 3| 
	 *		+--+--+--+--+
	 *		| 1| 2| 3| 4| 
	 *      +--+--+--+--+ 
	 *		| 2| 3| 4| 5| 
	 *		+--+--+--+--+
	 *		| 3| 4| 5| 6| 
	 *      +--+--+--+--+ 
	 */
	if(game_over(g))
		test_ok = false;

	set_tile(g, 0, 0, 10);
	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		|10| 1| 2| 3| 
	 *		+--+--+--+--+
	 *		| 1| 2| 3| 4| 
	 *      +--+--+--+--+ 
	 *		| 2| 3| 4| 5| 
	 *		+--+--+--+--+
	 *		| 3| 4| 5| 6| 
	 *      +--+--+--+--+ 
	 */
	if(!game_over(g))
		test_ok = false;

	set_tile(g, GRID_SIDE - 1, GRID_SIDE - 1, ((GRID_SIDE - 1) * 2) - 1);
	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		|10| 1| 2| 3| 
	 *		+--+--+--+--+
	 *		| 1| 2| 3| 4| 
	 *      +--+--+--+--+ 
	 *		| 2| 3| 4| 5| 
	 *		+--+--+--+--+
	 *		| 3| 4| 5| 5| 
	 *      +--+--+--+--+ 
	 */
	if(game_over(g))
		test_ok = false;

	delete_grid(g);

	if(!test_ok)
		return EXIT_FAILURE;

	printf("test ok!\n");
	return EXIT_SUCCESS;
}

/*
 * Fichier de test du module grid - test_can_move()
 * Affiche si le mouvement de la grille est possible ou non
 */
#include <stdlib.h>
#include <stdio.h>

#include <grid.h>

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

	if(!can_move(g, UP))
		test_ok = false;
	if(can_move(g, RIGHT))
		test_ok = false;
	if(!can_move(g, LEFT))
		test_ok = false;
	if(can_move(g, DOWN))
		test_ok = false;

	set_tile(g, 0, 0, 2);
	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		| 2| 1| 2| 3| 
	 *		+--+--+--+--+
	 *		| 1| 2| 3| 4| 
	 *      +--+--+--+--+ 
	 *		| 2| 3| 4| 5| 
	 *		+--+--+--+--+
	 *		| 3| 4| 5| 6| 
	 *      +--+--+--+--+ 
	 */
	if(can_move(g, UP))
		test_ok = false;
	if(can_move(g, RIGHT))
		test_ok = false;
	if(can_move(g, LEFT))
		test_ok = false;
	if(can_move(g, DOWN))
		test_ok = false;

	set_tile(g, GRID_SIDE - 1, GRID_SIDE - 1, 0);
	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		| 2| 1| 2| 3| 
	 *		+--+--+--+--+
	 *		| 1| 2| 3| 4| 
	 *      +--+--+--+--+ 
	 *		| 2| 3| 4| 5| 
	 *		+--+--+--+--+
	 *		| 3| 4| 5| 0| 
	 *      +--+--+--+--+ 
	 */
	if(can_move(g, UP))
		test_ok = false;
	if(!can_move(g, RIGHT))
		test_ok = false;
	if(can_move(g, LEFT))
		test_ok = false;
	if(!can_move(g, DOWN))
		test_ok = false;


	delete_grid(g);
	if(!test_ok)
		return EXIT_FAILURE;

	printf("test ok !\n");
	return EXIT_SUCCESS;
}

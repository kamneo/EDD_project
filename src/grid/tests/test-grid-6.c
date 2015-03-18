/*
 * Fichier de test du module grid - test_do_move()
 * test de jouer dans les 4 directions et si le score change de la bonne façon
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <grid.h>

int main (int argc, char** argv)
{
	if(GRID_SIDE < 4){
		printf("Ce test n'est pas adapter la taille de la grille est trop petite.\nLa taille minimale est 4.\n");
		return EXIT_FAILURE;
	}

	srand(time(NULL));
	grid g;
	g = new_grid ();
	bool test_UP_ok = true;
	bool test_DOWN_ok = true;
	bool test_LEFT_ok = true;
	bool test_RIGHT_ok = true;

	set_tile (g, 0, 0, 2);
	set_tile (g, 0, 1, 2);
	set_tile (g, 0, 2, 4);
	set_tile (g, 0, 3, 4);

	set_tile (g, 1, 1, 2);
	set_tile (g, 1, 2, 2);

	set_tile (g, 2, 0, 2);
	set_tile (g, 2, 3, 2);

	set_tile (g, 3, 1, 2);
	set_tile (g, 3, 3, 4);


	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		| 2| 2| 4| 4| 
	 *		+--+--+--+--+
	 *		| 0| 2| 2| 0| 
	 *      +--+--+--+--+ 
	 *		| 2| 0| 2| 0| 
	 *		+--+--+--+--+
	 *		| 0| 2| 0| 4| 
	 *      +--+--+--+--+ 
	 */

	do_move(g, LEFT);
	if(get_tile(g, 0, 0) != 4)
		test_LEFT_ok = false;
	if(get_tile(g, 0, 1) != 8)
		test_LEFT_ok = false;
	if(get_tile(g, 1, 0) != 4)
		test_LEFT_ok = false;
	if(get_tile(g, 2, 0) != 4)
		test_LEFT_ok = false;
	if(get_tile(g, 3, 0) != 2)
		test_LEFT_ok = false;
	if(get_tile(g, 3, 1) != 4)
		test_LEFT_ok = false;

	// le score doit etre 20
	if(grid_score(g) != 20)
		test_LEFT_ok = false;

	if(!test_LEFT_ok)
		printf("erreur lors du do_move(LEFT) ou du grid_score(LEFT) ici le score doit valoir 20.(%d)\n", grid_score(g));
	
	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		| 4| 8| 0| 0| 
	 *		+--+--+--+--+
	 *		| 4| 0| 0| 0| 
	 *      +--+--+--+--+ 
	 *		| 4| 0| 0| 0| 
	 *		+--+--+--+--+
	 *		| 2| 4| 0| 0| 
	 *      +--+--+--+--+ 
	 */
	do_move(g, UP);
	if(get_tile(g, 0, 0) != 8)
		test_UP_ok = false;
	if(get_tile(g, 0, 1) != 8)
		test_UP_ok = false;
	if(get_tile(g, 1, 0) != 4)
		test_UP_ok = false;
	if(get_tile(g, 1, 1) != 4)
		test_UP_ok = false;
	if(get_tile(g, 2, 0) != 2)
		test_UP_ok = false;

	// le score doit etre 28
	if(grid_score(g) != 28)
		test_UP_ok = false;

	if(!test_UP_ok)
		printf("erreur lors du do_move(UP) ou du grid_score(UP) ici le score doit valoir 28.(%d)\n", grid_score(g));

	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		| 8| 8| 0| 0| 
	 *		+--+--+--+--+
	 *		| 4| 4| 0| 0| 
	 *      +--+--+--+--+ 
	 *		| 2| 0| 0| 0| 
	 *		+--+--+--+--+
	 *		| 0| 0| 0| 0| 
	 *      +--+--+--+--+ 
	 */
	do_move(g, RIGHT);
	if(get_tile(g, 0, GRID_SIDE - 1) != 16)
		test_RIGHT_ok = false;
	if(get_tile(g, 1, GRID_SIDE - 1) != 8)
		test_RIGHT_ok = false;
	if(get_tile(g, 3, GRID_SIDE - 1) != 2)
		test_RIGHT_ok = false;

	// le score doit etre 52
	if(grid_score(g) != 52)
		test_RIGHT_ok = false;

	if(!test_RIGHT_ok)
		printf("erreur lors du do_move(RIGHT) ou du grid_score(RIGHT) ici le score doit valoir 52.(%d)\n", grid_score(g));
	
	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		| 0| 0| 0|16| 
	 *		+--+--+--+--+
	 *		| 0| 0| 0| 8| 
	 *      +--+--+--+--+ 
	 *		| 0| 0| 0| 2| 
	 *		+--+--+--+--+
	 *		| 0| 0| 0| 0| 
	 *      +--+--+--+--+ 
	 */
	
	// on triche un peu =)
	set_tile(g, 3, GRID_SIDE - 1, 8);
	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		| 0| 0| 0|16| 
	 *		+--+--+--+--+
	 *		| 0| 0| 0| 8| 
	 *      +--+--+--+--+ 
	 *		| 0| 0| 0| 8| 
	 *		+--+--+--+--+
	 *		| 0| 0| 0| 0| 
	 *      +--+--+--+--+ 
	 */

	do_move(g, DOWN);
	if(get_tile(g, GRID_SIDE - 2, GRID_SIDE - 1) != 16)
		test_DOWN_ok = false;
	if(get_tile(g, GRID_SIDE - 1, GRID_SIDE - 1) != 16)
		test_DOWN_ok = false;
	// le score doit etre 68
	if(grid_score(g) != 68)
		test_DOWN_ok = false;

	if(!test_DOWN_ok)
		printf("erreur lors du do_move(DOWN) ou du grid_score(DOWN) ici le score doit valoir 68.(%d)\n", grid_score(g));
	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		| 0| 0| 0| 0| 
	 *		+--+--+--+--+
	 *		| 0| 0| 0| 0| 
	 *      +--+--+--+--+ 
	 *		| 0| 0| 0|16| 
	 *		+--+--+--+--+
	 *		| 0| 0| 0|16| 
	 *      +--+--+--+--+ 
	 */

	do_move(g, DOWN);
	if(get_tile(g, GRID_SIDE - 1, GRID_SIDE - 1) != 32)
		test_DOWN_ok = false;
	// le score doit etre 
	if(grid_score(g) != 100)
		test_DOWN_ok = false;

	if(!test_DOWN_ok)
		printf("erreur lors du do_move(DOWN) ou du grid_score(DOWN) ici le score doit valoir 100.(%d)\n", grid_score(g));

	/*
	 *      la grille vaut : 
	 *		+--+--+--+--+
	 *		| 0| 0| 0| 0| 
	 *		+--+--+--+--+
	 *		| 0| 0| 0| 0| 
	 *      +--+--+--+--+ 
	 *		| 0| 0| 0| 0| 
	 *		+--+--+--+--+
	 *		| 0| 0| 0|32| 
	 *      +--+--+--+--+ 
	 */
	delete_grid(g);
	if(!test_UP_ok || !test_DOWN_ok || !test_RIGHT_ok || !test_LEFT_ok)
		return EXIT_FAILURE;

	printf("test ok !\n");
	return EXIT_SUCCESS;
}
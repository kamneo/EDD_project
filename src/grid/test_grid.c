/*
 * Fichier de test du module grid
 */
#include <stdlib.h>
#include <stdio.h>

#include "grid.h"
#include "affichage.h"
#include "utilities.h"

int main (int arc, char** argv)
{
	grid g;
	g = new_grid ();

	/*printf("affichage de la grille lors de la création ! \n");
	display_grid(g);

	printf("le résultat de la grille est : %lu\n", grid_score(g));
	
	printf("modification de la grille \n");
	set_tile (g, 0, 0, 2);
	set_tile (g, 0, 1, 2);
	set_tile (g, 0, 2, 4);
	set_tile (g, 0, 3, 4);

	set_tile (g, 1, 1, 2);
	set_tile (g, 1, 2, 2);

	set_tile (g, 2, 3, 2);
	set_tile (g, 2, 0, 2);

	set_tile (g, 3, 3, 4);
	set_tile (g, 3, 1, 2);
	display_grid(g);

	printf("la grille %s bouger vers le haut !\n", can_move(g, UP)? "peut" : "ne peut pas");

	printf("la grille %s bouger vers le bas !\n", can_move(g, DOWN)? "peut" : "ne peut pas");

	printf("la grille %s bouger vers la droite!\n", can_move(g, RIGHT)? "peut" : "ne peut pas");

	printf("la grille %s bouger vers la gauche!\n", can_move(g, LEFT)? "peut" : "ne peut pas");
	do_move(g, RIGHT);
	display_grid(g);
	do_move(g, RIGHT);
	display_grid(g);
	do_move(g, LEFT);
	display_grid(g);
	do_move(g, UP);
	display_grid(g);
	do_move(g, DOWN);
	display_grid(g);

	add_tile(g);
	display_grid(g);
	delete_grid (g);

	g = new_grid ();*/
	display_grid(g);
	play(g, LEFT);
	display_grid(g);
	play(g, RIGHT);
	display_grid(g);
	play(g, UP);
	display_grid(g);
	play(g, DOWN);
	display_grid(g);
	return EXIT_SUCCESS;
}


/*
 * Fichier de test du module grid
 * Affiche si le mouvement de la grille est possible ou non
 */
#include <stdlib.h>
#include <stdio.h>

#include "grid.h"
#include "affichage.h"

int main (int arc, char** argv)
{
	grid g;
	g = new_grid ();

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

	printf("%s", can_move(g, UP)? "1" : "0");
	printf("%s", can_move(g, DOWN)? "1" : "0");
	printf("%s", can_move(g, RIGHT)? "1" : "0");
	printf("%s\n", can_move(g, LEFT)? "1" : "0");

	return EXIT_SUCCESS;
}
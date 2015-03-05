/*
 * Fichier de test du module grid
 * Affiche la grille apres un mouvement
 */
#include <stdlib.h>
#include <stdio.h>

#include <grid.h>
#include <affichage.h>

int main (int argc, char** argv)
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

	do_move(g, RIGHT);
	do_move(g, LEFT);
	do_move(g, UP);
	do_move(g, DOWN);
	
	light_display_grid(g);

	return EXIT_SUCCESS;
}

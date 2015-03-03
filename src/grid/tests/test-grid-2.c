/*
 * Fichier de test du module grid
 * Affiche la grille après l'ajout d'une tile aléatoire et set_tile
 */
#include <stdlib.h>
#include <stdio.h>

#include "grid.h"
#include "affichage.h"
#include "utilities.h"

 int main (int arc, char** argv){
 	grid g;
	g = new_grid ();

	add_tile (g);

	set_tile(g, 0, 0, 2);

	light_display_grid (g);

	return EXIT_SUCCESS;
 }
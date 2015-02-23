/*
 * Fichier de test du module grid
 * Affiche la grille à la création
 */
#include <stdlib.h>
#include <stdio.h>

#include "grid.h"
#include "affichage.h"
#include "utilities.h"

 int main (int arc, char** argv){
 	grid g;
	g = new_grid ();

	light_display_grid (g);
	
	return EXIT_SUCCESS;
 }
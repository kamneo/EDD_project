/*
 * Fichier de test du module grid
 * Affiche la grille à la création
 */
#include <stdlib.h>
#include <stdio.h>

#include <grid.h>
#include <affichage.h>

 int main (int argc, char** argv){
 	grid g;
	g = new_grid ();

	light_display_grid (g);
	
	return EXIT_SUCCESS;
 }

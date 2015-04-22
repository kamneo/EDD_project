#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
/**
 * \file affichage.c
 * \brief Contient les fonctions d'affichage standard de la grille.
 **/

#include "affichage.h"

/**
 * \brief Calcule (valeur_tile)^2
 * \param t, la tuile à calculer
 * \return la puissance de la tuile si t>0 ou retourne 0
 */
static unsigned long int pow_of_2(tile t) {
	if (t == 0)
		return t;
	return pow(2, t);
}

/**
 * \brief Affiche en console la grille avec des couleurs et la puissance des valeurs contenues dans les tuiles
 */
void display_grid(grid g) {

	for (int i = 0; i < GRID_SIDE * 2 + 1; i++) {
		if (i % 2 == 0)
			if (i != 0)
				printf("|\n+");
			else
				printf("+");
		else
			printf("\n");

		for (int j = 0; j < GRID_SIDE; j++)
			if (i % 2 != 0) {
				if (get_tile(g, i / 2, j) == 0)
					printf("| \t");
				else
					// affiche les puissances de 2 avec les couleurs
					printf("|\x1B[48;5;%dm%lu\t\033[0m",
							get_tile(g, i / 2, j) % 10 + 1,
							pow_of_2(get_tile(g, i / 2, j)));
			} else {
				printf("-------+");
			}
	}

	printf("\n le score est de : %lu \n\n", grid_score(g));
}

/**
 * \brief Affiche en console la grille avec des couleurs et la valeur contenue dans les tuiles
 */
void display_normal_grid(grid g) {

	for (int i = 0; i < GRID_SIDE * 2 + 1; i++) {
		if (i % 2 == 0)
			if (i != 0)
				printf("|\n+");
			else
				printf("+");
		else
			printf("\n");

		for (int j = 0; j < GRID_SIDE; j++)
			if (i % 2 != 0) {
				printf("|\x1B[48;5;%dm%lu\t\033[0m",
						get_tile(g, i / 2, j) % 10 + 1,
						(long unsigned int) (get_tile(g, i / 2, j)));
			} else {
				printf("-------+");
			}
	}

	printf("\n le score est de : %lu \n\n", grid_score(g));
}

/**
 * \brief Affiche en console la grille sans les cases, juste les valeurs des cases sur une ligne
 */
void light_display_grid(grid g) {
	for (int i = 0; i < GRID_SIDE; i++) {
		for (int j = 0; j < GRID_SIDE; j++)
			printf("%lu", (long unsigned int) (get_tile(g, i / 2, j)));
	}
}

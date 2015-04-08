#include "strategy.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef struct s_resultat resultat;

struct s_resultat {
	double meilleur_score;
	dir direction;
};

dir strategie_coin_1(strategy s, grid g);
dir strategie_coin_2(strategy s, grid g);
double eval(grid g);
double progressive(grid g);
double reguliere(grid g);

void free_memless_strat(strategy strat) {
	free(strat->mem);
	free(strat);
}

strategy A2_bonnet_borde_pinero_basic() {
	strategy strat = malloc(sizeof(struct strategy_s)); //initialisation de notre structure strategy
	strat->name = "Strategie du coin 1";				// Nom de la strategie
	strat->play_move = strategie_coin_1; 				//cf strategy.c
	strat->mem = malloc(sizeof(int));

	*(int*) (strat->mem) = 0; // on pointe sur un int qui sera un compteur de tour jouer(pour certaine strat)

	strat->free_strategy = free_memless_strat;

	return strat;
}

/*
 * premiere strategie appelée stratégie du coin
 * param : strategy s la structure stratégie
 * param : grid la grille
 * return: la direction optimale à jouer qui a été calculée par cette stratégie
 */
dir strategie_coin_1(strategy s, grid g) {
	printf("%f", eval(g));
	if (can_move(g, LEFT)) {
		return LEFT;
	} else if (can_move(g, DOWN)) {
		return DOWN;
	} else if (can_move(g, RIGHT)) {
		return RIGHT;
	} else if (can_move(g, UP)) {
		return UP;
	}

	return -1;
}

/*
 * deuxième strategie qui reprend la stratégie du coin mais qui un tour sur deux
 * changera l'ordre des mouvements favoris.
 * param : strategy s la sutructure stratégie
 * param : grid la grille
 * return: la direction optimale à jouer qui a été calculée par cette stratégie
 */
dir strategie_coin_2(strategy s, grid g) {
	int* val = s->mem;

	(*val)++;

	if ((*val) % 2 == 0) {
		if (can_move(g, LEFT)) {
			return LEFT;
		} else if (can_move(g, DOWN)) {
			return DOWN;
		}
	} else {
		if (can_move(g, DOWN)) {
			return DOWN;
		} else if (can_move(g, LEFT))
			return LEFT;
	}

	if (can_move(g, RIGHT)) {
		return RIGHT;
	} else if (can_move(g, UP)) {
		return UP;
	} else
		return -1;
}

/*dir rapide_strategie(grid g,  int profondeur) {
 int nb_directions = 4;
 dir direction = dir[0];

 for (int iterator = 0; iterator < nb_directions; ++iterator) {
 grid grid_clone = new_grid();
 copy_grid(g, grid_clone);

 if (can_move(grid_clone, dir[iterator])) {
 play(grid_clone, dir[iterator]);

 if (win(grid_clone)){
 delete_grid(grid_clone);
 return dir[iterator];
 }

 if (profondeur == 0) {
 meilleur_eval = &eval + eval(grid_clone);
 } else {
 rapide_strategie(grid_clone, profondeur - 1, *eval);
 }
 }

 delete_grid(grid_clone);
 }
 return LEFT;
 }*/

/*
 * fonction qui regarde si on a atteint 2048
 * param : grid g la grille courante
 * return: true si on a atteint 2048 sinon false.
 */
bool win(grid g) {
	for (int x = 0; x < GRID_SIDE; ++x) {
		for (int y = 0; y < GRID_SIDE; ++y) {
			if (get_tile(g, x, y) == 11)
				return true;
		}
	}
	return false;
}

/*
 * fonction qui évalue le poids de la grille
 * param : g qui est la grille à évaluer
 * return: double qui est la valeur de la grille
 */
double eval(grid g) {
	// emptyCells qui compte le nombre de tile vide
	// maxValue qui contient la plus grande valeur de la grille
	int emptyCells = 0, maxValue = 0;

	for (int x = 0; x < GRID_SIDE; ++x) {
		for (int y = 0; y < GRID_SIDE; ++y) {
			if (get_tile(g, x, y) == 0)
				emptyCells++;
			else if (get_tile(g, x, y) > maxValue)
				maxValue = get_tile(g, x, y);
		}
	}

	// Coeficient d'imporance rapport à la grille.
	double smoothWeight = 0.1, monoWeight = 1.0, emptyWeight = 2.7, maxWeight =
			1.0;

	return progressive(g) * smoothWeight + reguliere(g) * monoWeight +
			log(emptyCells) * emptyWeight + maxValue * maxWeight;
}

/**
 * fonction qui donne une note comprise entre 1 et 0 sur sur la régularité de la grille.
 * c'est a dire si les valeurs ce suivent, on preferera avoir une suite 2 - 4 - 8 - 16,
 * plutot que 2 - 16 - 64 - 128
 * param : grid g qui est la grille à évaluer
 * return : double le score quelle a obtenue.
 */
double reguliere(grid g) {
double bareme = 1. / (GRID_SIDE * GRID_SIDE);
double score = 1.;

for (int x = 0; x < GRID_SIDE; ++x) {
	for (int y = 0; y < GRID_SIDE; ++y) {
		// on verifie que la tile ne soit pas nulle
		if (get_tile(g, x, y) != 0) {
			// la tile sous la tile courante doit etre superieure de 1
			if (y < GRID_SIDE - 1 && get_tile(g, x, y + 1) != 0
					&& (get_tile(g, x, y) + 1) != get_tile(g, x, y + 1))
				score -= bareme / 2.;
			// la tile à gauche de la tile courante doit etre superieure de 1
			if (x > 0 && get_tile(g, x - 1, y) != 0
					&& (get_tile(g, x, y) + 1) != get_tile(g, x - 1, y))
				score -= bareme / 2.;
		}
	}
}

return score;
}

/**
 * fonction qui donne une note comprise entre 1 et 0 sur sur la progressivité de la grille.
 * C'est à dire lorsque la valeur des cases augmente ou descend quelle que soit la direction.
 * Ainsi, 2 - 4 - 8 - 16 est acceptable, tout comme 32 - 8 - 4 -2.
 * Mais 2 - 8 - 2 - 16 ne l'est pas.
 * param : grid g qui est la grille à évaluer
 * return : double le score quelle a obtenue.
 */
double progressive(grid g) {
double bareme = 1. / (GRID_SIDE * GRID_SIDE);
double score = 1.;

for (int x = 0; x < GRID_SIDE; ++x) {
	for (int y = 0; y < GRID_SIDE; ++y) {
		// on verifie que la tile ne soit pas nulle
		if (get_tile(g, x, y) != 0) {
			// la tile sous la tile courante doit etre superieure
			if (y < GRID_SIDE - 1 && get_tile(g, x, y) > get_tile(g, x, y + 1))
				score -= bareme;
			// la tile à gauche de la tile courante doit etre superieure
			if (x > 0 && get_tile(g, x, y) > get_tile(g, x - 1, y))
				score -= bareme;
		}
	}
}

return score;
}

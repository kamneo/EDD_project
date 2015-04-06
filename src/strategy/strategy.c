#include "strategy.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct s_resultat resultat;

struct s_resultat {
	double meilleur_score;
	dir direction;
};

dir strategie_coin_2(strategy s, grid g);
dir strategie_coin_1(strategy s, grid g);


void free_memless_strat(strategy strat) {
	free(strat->mem);
	free(strat);
}

strategy A2_pinero_borde_bonnet(grid g){
	strategy strat = malloc(sizeof(struct strategy_s)); //initialisation de notre structure strategy
	strat->name = "Strategie du coin";						// Nom de la strategie
	strat->play_move = strategie_coin_1; 		//cf strategy.c
	strat->mem = malloc(sizeof(int));

	*(int*) (strat->mem) = 0; // on pointe sur un int qui sera un compteur de tour jouer(pour certaine strat)

	strat->free_strategy = free_memless_strat;

	return strat;
}

/*
 * deuwième strategie qui reprend la stratégie du coin mais qui un tour sur deux
 * changera l'ordre des mouvements favori.
 * param : strategy s la sutructure stratégie
 * param : grid la grille
 * return: la direction optimal à jouer qui a été calculé par cette stratégie
 */
dir strategie_coin_2(strategy s, grid g) {
	int* val = s->mem;
	if ((*val) % 2 == 0) {
		if (can_move(g, LEFT)) {
			return LEFT;
		} else if (can_move(g, DOWN)) {
			return DOWN;
		} else if (can_move(g, RIGHT)) {
			return RIGHT;
		} else {
			return UP;
		}
	} else {
		if (can_move(g, DOWN)) {
			return DOWN;
		} else if (can_move(g, LEFT)) {
			return LEFT;
		} else if (can_move(g, RIGHT)) {
			return RIGHT;
		} else {
			return UP;
		}
	}

	(*val)++;
}

/*
 * premiere strategie appeler stratégie du coin
 * param : strategy s la sutructure stratégie
 * param : grid la grille
 * return: la direction optimal à jouer qui a été calculé par cette stratégie
 */
dir strategie_coin_1(strategy s, grid g) {

	if (can_move(g, LEFT)) {
		return LEFT;
	} else if (can_move(g, DOWN)) {
		return DOWN;
	} else if (can_move(g, UP)) {
		return UP;
	} else {
		return RIGHT;
	}
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
 * fonction qui évalue le poid de la grille
 * param : g qui est la grille à évaluer
 * return: double qui est la valeur de la grille
 */
/*double eval(grid g) {
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

	return smoothness() * smoothWeight + monotonicity() * monoWeight +
	Math.log(emptyCells)emptyCells * emptyWeight + maxValue() * maxWeight;
}*/

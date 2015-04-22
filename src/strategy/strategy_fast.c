/**
 * \file strategy_fast.c
 * \brief contient la stratégie rapide
 */


#include "strategy_fast.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

/**
 * brief la profondeur de calcul
*/
#define DEPTH 2


struct s_result {
	double score;
	dir direction;
};

typedef struct s_result result;

dir corner_strategy_1(strategy s, grid g);
dir corner_strategy_2(strategy s, grid g);
dir strategy_fast(strategy s, grid g);
result max(grid g, int depth);
double eval(grid g);
double progressive(grid g);
double regular(grid g);
void do_expected(grid g, result* res, dir direction, int depth);
double expected(grid g, int depth);

void free_memless_strat(strategy strat) {
	free(strat->mem);
	free(strat);
}

strategy A2_bonnet_borde_pinero_fast() {
	strategy strat = malloc(sizeof(struct strategy_s)); //initialisation de notre structure strategy
	strat->name = "Strategie du fast";				// Nom de la strategie
	strat->play_move = strategy_fast; 				//cf strategy.c
	strat->mem = malloc(sizeof(int));

	*(int*) (strat->mem) = 0; // on pointe sur un int qui sera un compteur de tour jouer(pour certaine strat)

	strat->free_strategy = free_memless_strat;

	return strat;
}

/**
 * \brief première stratégie appelée stratégie du coin
 * \param s la structure stratégie
 * \param g, la grille
 * \return la direction optimale à jouer qui a été calculée par cette stratégie
 */
dir corner_strategy_1(strategy s, grid g) {

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

/**
 * \brief deuxième stratégie qui reprend la stratégie du coin mais qui un tour sur deux
 * changera l'ordre des mouvements favoris
 * \param s, la sutructure stratégie
 * \param g, la grille
 * \return la direction optimale à jouer qui a été calculée par cette stratégie
 */
dir corner_strategy_2(strategy s, grid g) {
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

/**
 * \brief stratégie basée sur expected max qui retourne la direction optimale à jouer
 * \param s, la sutructure stratégie
 * \param g, la grille
 * \return la direction optimale à jouer qui a été calculée par cette stratégie
 */
dir strategy_fast(strategy strat, grid g) {
	// initialisation de la structure résultat
	result res;
	res.score = 0;
	res.direction = -1;

	res = max(g, DEPTH);

	return res.direction;
}

result max(grid g, int depth)
{
	result bestRes;

	// pour chaque direction possible ont fait le traitement expected();
	do_expected(g, &bestRes, LEFT, depth);
	do_expected(g, &bestRes, RIGHT, depth);
	do_expected(g, &bestRes, DOWN, depth);
	do_expected(g, &bestRes, UP, depth);

	return bestRes;
}

/**
 * \brief fonction qui pour une direction calcule la valeur moyenne de toutes les grilles
 * possibles et si le résultat est plus grand que celui contenu dans la structure résultat
 * modifie les champs de la structure avec les nouvelles valeurs (direction, score)
 * \param g la grille
 * \param bestRes un pointeur sur la structure résultat
 * \param direction, la direction choisi
 */
void do_expected(grid g, result* bestRes, dir direction, int depth)
{
	double expect = 0;

	// création d'une nouvelle grille sur laquelle on fera les statistiques
	grid ng = new_grid();
	copy_grid(g, ng);

	if (can_move(ng, direction)) {

		do_move(ng, direction);
		expect = expected(ng, depth);

		if(expect >= bestRes->score)
		{
			bestRes->score = expect;
			bestRes->direction = direction;
		}
	}

	delete_grid(ng);
}

/**
 * \brief fonction qui calcule la valeur de chaque grille qui peuvent etre générées pour une direction
 * et retourne le score moyen de toutes ces grilles
 * \param g, la grille
 * \param direction, la direction choisi
 * \return la valeur moyenne de chaque grille dans une direction
 */
double expected(grid g, int depth)
{
	// création du pointeur de fonction sur la fonction d'évaluation de la grille
	double (*evaluation)(grid);
	evaluation = eval;

	int emptyCells = 0;		// nombre de tuile vides
	double score_2 = 0.;	//somme des scores si la tuile introduite est un 2
	result res;

	// pour chaque tuile vide on évalue la grille
	for (int x = 0; x < GRID_SIDE; ++x) {
		for (int y = 0; y < GRID_SIDE; ++y) {
			if(get_tile(g, x, y) == 0){
				emptyCells++;
				// si la tuile est vide on y met la valeur 1 et on fait eval()
				set_tile(g, x, y, 1);
				score_2 += evaluation(g);
				//
				if(depth > 0)
				{
					res = max(g, depth - 1);
					score_2 += res.score;
				}

				// on remet la tuile à 0
				set_tile(g, x, y, 0);
			}
		}
	}

	// on retourne le score moyen de la grille pour cette direction
	double score = (score_2) / emptyCells;

	return score;
}

/**
 * \brief fonction qui évalue le poids de la grille
 * \param g qui est la grille à évaluer
 * \return la valeur de la grille
 */
double eval(grid g) {
	// emptyCells qui compte le nombre de tuiles vides
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

	// Coefficient d'importance par rapport à la grille
	double 	smoothWeight =  1.,
			monoWeight = 2.,
			emptyWeight = 1.,
			maxWeight = 2.;

	return progressive(g) * smoothWeight + regular(g) * monoWeight
			+ emptyCells * emptyWeight + maxValue * maxWeight;
}

/**
 * fonction qui donne une note comprise entre 1 et 0 sur sur la régularité de la grille
 * c'est-à-dire si les valeurs se suivent, on préfèrera avoir une suite 2 - 4 - 8 - 16,
 * plutôt que 2 - 16 - 64 - 128
 * paramètre g, qui est la grille à évaluer
 * retourne le score qu'elle a obtenu
 */
double regular(grid g) {
	double bareme = 1. / (GRID_SIDE * GRID_SIDE);
	double score = 1.;

	for (int x = 0; x < GRID_SIDE; ++x) {
		for (int y = 0; y < GRID_SIDE; ++y) {
			// on vérifie que la tuile ne soit pas nulle
			if (get_tile(g, x, y) != 0) {
				// la tuile sous la tuile courante doit être superieure de 1
				if (y < GRID_SIDE - 1 && get_tile(g, x, y + 1) != 0
						&& (get_tile(g, x, y) + 1) != get_tile(g, x, y + 1))
					score -= bareme / 2.;
				// la tuile à gauche de la tile courante doit être superieure de 1
				if (x > 0 && get_tile(g, x - 1, y) != 0
						&& (get_tile(g, x, y) + 1) != get_tile(g, x - 1, y))
					score -= bareme / 2.;
			}
		}
	}

	return score;
}

/**
 * fonction qui donne une note comprise entre 1 et 0 sur sur la progressivité de la grille
 * C'est-à-dire lorsque la valeur des cases augmente ou descend quelque soit la direction
 * Ainsi, 2 - 4 - 8 - 16 est acceptable, tout comme 32 - 8 - 4 -2.
 * Mais 2 - 8 - 2 - 16 ne l'est pas
 * paramètre g, qui est la grille à évaluer
 * retourne le score quelle a obtenu
 */
double progressive(grid g) {
	double bareme = 1. / (GRID_SIDE * 2);
	double score = 1.;

	for (int x = 0; x < GRID_SIDE; ++x) {
		for (int y = 0; y < GRID_SIDE; ++y) {
			// on vérifie que la tuile ne soit pas nulle
			if (get_tile(g, x, y) != 0) {
				// la tuile sous la tuile courante doit être supérieure
				if (y < GRID_SIDE - 1
						&& get_tile(g, x, y) > get_tile(g, x, y + 1))
					score -= bareme;
				// la tuile à gauche de la tuile courante doit être supérieure
				if (x > 0 && get_tile(g, x, y) > get_tile(g, x - 1, y))
					score -= bareme;
			}
		}
	}

	return score;
}

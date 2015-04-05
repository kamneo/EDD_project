/**
 * \file	strategy.h
 * \versions	1.0
 * \brief	Defines the "strategy" structure
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "grid.h"

/** \b strategy is a pointer to a strategy_s structure */
typedef struct strategy_s *strategy;

/**
 * \b Structure that contains a strategy.
 *
 * A strategy is essentially a function (play_move) which, given a partially
 * filled grid, picks the next direction to be played. More advanced strategies
 * may require a history of previously played moves (or even games) ; in such
 * cases, a strategy may use the <mem> field to store such information.
 */
struct strategy_s {
	void* mem; /** Points the the data stored by the strategy. */
	char* name; /** The strategy's name. This will be used to display the tournament scores. */
	dir (*play_move)(strategy, grid); /** A function which returns the direction chosen by the strategy. The first parameter is a pointer to the current strategy (useless for memoryless strategies). The second one is the current grid. */
	void (*free_strategy)(strategy); /** Frees any resources allocated during the strategy's creation (<name>, <mem>, ...). */
};

/*
 * deuwième strategie qui reprend la stratégie du coin mais qui un tour sur deux
 * changera l'ordre des mouvements favori.
 * param : strategy s la sutructure stratégie
 * param : grid la grille
 * return: la direction optimal à jouer qui a été calculé par cette stratégie
 */
dir strategie_coin_2(strategy s, grid g);

/*
 * premiere strategie appeler stratégie du coin
 * param : strategy s la sutructure stratégie
 * param : grid la grille
 * return: la direction optimal à jouer qui a été calculé par cette stratégie
 */
dir strategie_coin_1(strategy s, grid g);

/**
 * Naively frees the <strat> pointer.
 */
extern void free_memless_strat(strategy strat);

#endif /* STRATEGY_H_ */

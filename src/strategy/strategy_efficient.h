/*
 * strategy_efficient.h
 *
 *  Created on: Apr 9, 2015
 *      Author: debian
 */

#ifndef SRC_STRATEGY_STRATEGY_EFFICIENT_H_
#define SRC_STRATEGY_STRATEGY_EFFICIENT_H_

#include "strategy.h"
#include <grid.h>


/*
 * stratégie capable de jouer au 2048 en moins de 2 minutes
 * param : strategy s la structure stratégie
 * param : grid la grille
 * return: la direction optimale à jouer qui a été calculée par cette stratégie
 */
strategy A2_bonnet_borde_pinero_efficient();

#endif /* SRC_STRATEGY_STRATEGY_EFFICIENT_H_ */

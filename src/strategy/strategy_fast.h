/**
 * \file strategy_fast.h
 * \brief contient la stratégie rapide
 */


#ifndef SRC_STRATEGY_STRATEGY_FAST_H_
#define SRC_STRATEGY_STRATEGY_FAST_H_


#include "strategy.h"
#include <grid.h>


/**
 * \brief stratégie capable de jouer au 2048 en moins de 10 secondes
 * \param s la structure stratégie
 * \param g la grille
 * \return la direction optimale à jouer qui a été calculée par cette stratégie
 */
strategy A2_bonnet_borde_pinero_fast();

#endif /* SRC_STRATEGY_STRATEGY_FAST_H_ */

/*
 * affichage.h
 *
 *  Created on: Apr 8, 2015
 *      Author: debian
 */
#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_
/**
 * \file affichage.h
 * \brief Contains functions needed to play 2048run grid.c.
 **/

#include "grid.h"

/**
 * \brief Display in console the grid with color and the pow of value contained in tile
 */
extern void display_grid(grid g);

/**
 * \brief Display in console the grid with color and the value contained in tile
 */
extern void display_normal_grid(grid g);

/**
 * \brief Display in console the grid without form just numbres in only one line
 */
extern void light_display_grid(grid g);

#endif


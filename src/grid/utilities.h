#ifndef _UTILITIES_H_
#define _UTILITIES_H_
/**
 * \file utilities.h
 * \brief Contains functions needed to compile grid.o.
 **/

#include "grid.h"

/**
 * \brief verify if the lign can move in the direction
 * \param g the grid
 * \param i the curent lign
 * \param debut the first indice worked 0 if the direction is LEFT and GRID_SIZE - 1 if the direction is RIGHT
 * \param fin the last indice worked 0 if the direction is RIGHT and GRID_SIZE - 1 if the direction is LEFT
 * \param facteur it's the variable needed for increment if the direction is RIGHT or increment
 * \return if the lign can move or not
 */
extern bool lign_can_move(grid g, int i, int debut, int fin, int facteur);


/**
 * \brief verify if the colone can move in the direction
 * \param g the grid
 * \param j the curent colone
 * \param debut the first indice worked 0 if the direction is LEFT and GRID_SIZE - 1 if the direction is DOWN
 * \param fin the last indice worked 0 if the direction is RIGHT and GRID_SIZE - 1 if the direction is LEFT
 * \param facteur it's the variable needed for increment if the direction is RIGHT or increment
 * \return if the colone can move or not
 */
extern bool colon_can_move(grid g, int j, int debut, int fin, int facteur);

/**
 * \brief do the move on a line in the grid 
 * \param g the grid
 * \param i the curent line
 * \param d the direction on the line (LEFT or RIGHt)
 */
extern void lign_do_move(grid g, int i, dir d);

/**
 * \brief do the move on a line in the grid 
 * \param g the grid
 * \param i the curent colone
 * \param d the direction on the colone (UP or DOWN)
 */
extern void colon_do_move(grid g, int i, dir d);

#endif

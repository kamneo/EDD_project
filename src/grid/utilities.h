#ifndef _UTILITIES_H_
#define _UTILITIES_H_
/**
 * \file utilities.h
 * \brief contient les fonctions nécessaires pour compiler grid.o
 **/

#include "grid.h"

/**
 * \Vérifie si la ligne peut bouger vers la direction
 * \paramètre g, la grille
 * \paramètre i la ligne en question
 * \paramètre start, le premier indice 0 si la direction est gauche, GRID_SIZE - 1 si la direction est droite
 * \paramètre end, le dernier indice 0 si la direction est droite, GRID_SIZE - 1  si la direction est gauche
 * \paramètre factor -1 si c'est un mouvement vers la gauche, 1 si vers la droite
 * \retourne vrai si la ligne peut bouger, faux sinon
 */
extern bool line_can_move(grid g, int i, int start, int end, int factor);

/**
 * \Vérifie si la colonne peut bouger dvers la direction
 * \paramètre g, la grille
 * \paramètre j, la colonne en question
 * \paramètre start le premier indice, 0 si la direction est haut GRID_SIZE - 1 si la direction est bas
 * \paramètre end le dernier indice, 0 si la direction est bas GRID_SIZE - 1 si la direction est haut
 * \paramètre factor -1 si c'est un mouvement vers le haut, 1 si vers le bas
 * \retourne vrai si la colonne peut bouger, faux sinon
 */
extern bool column_can_move(grid g, int j, int start, int end, int factor);

/**
 * \Fait le mouvement sur une ligne de la grille
 * \paramètre g, la grille
 * \paramètre i, la ligne en question
 * \paramètre d  la direction
 */
extern unsigned long int line_do_move(grid g, int i, dir d);

/**
 * \Fait le mouvement sur une colonne de la grille
 * \paramètre g, la grille
 * \paramètre j, la ligne en question
 * \paramètre d  la direction
 */
extern unsigned long int column_do_move(grid g, int i, dir d);

#endif

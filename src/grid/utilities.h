#ifndef _UTILITIES_H_
#define _UTILITIES_H_
/**
 * \fichier utilities.h
 * \contient les fonctions nécessaires pour compiler grid.o
 **/

#include "grid.h"

/**
 * \Vérifie si la ligne peut bouger vers la direction
 * \paramètre g, la grille
 * \paramètre i la ligne en question
 * \paramètre debut, le premier indice 0 si la direction est gauche, GRID_SIZE - 1 si la direction est droite
 * \paramètre fin, le dernier indice 0 si la direction est droite, GRID_SIZE - 1  si la direction est gauche
 * \paramètre facteur -1 si c'est un mouvement vers la gauche, 1 si vers la droite
 * \retourne vrai si la ligne peut bouger, faux sinon
 */
extern bool lign_can_move(grid g, int i, int debut, int fin, int facteur);

/**
 * \Vérifie si la colonne peut bouger dvers la direction
 * \paramètre g, la grille
 * \paramètre j, la colonne en question
 * \paramètre debut le premier indice, 0 si la direction est haut GRID_SIZE - 1 si la direction est bas
 * \paramètre fin le dernier indice, 0 si la direction est bas GRID_SIZE - 1 si la direction est haut
 * \paramètre facteur -1 si c'est un mouvement vers le haut, 1 si vers le bas
 * \retourne vrai si la colonne peut bouger, faux sinon
 */
extern bool column_can_move(grid g, int j, int debut, int fin, int facteur);

/**
 * \Fait le mouvement sur une ligne de la grille
 * \paramètre g, la grille
 * \paramètre i, la ligne en question
 * \paramètre d  la direction
 */
extern unsigned long int lign_do_move(grid g, int i, dir d);

/**
 * \Fait le mouvement sur une colonne de la grille
 * \paramètre g, la grille
 * \paramètre j, la ligne en question
 * \paramètre d  la direction
 */
extern unsigned long int column_do_move(grid g, int i, dir d);

#endif

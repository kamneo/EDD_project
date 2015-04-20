#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_
/**
 * \fichier affichage.h
 * \Contient les fonctions nécessaires pour afficher la grille
 **/

#include "grid.h"

/**
 * \Affiche en console la grille avec des couleurs et la puissance des valeurs contenues dans les tuiles
 */
extern void display_grid(grid g);

/**
 * \Affiche en console la grille avec des couleurs et la valeur contenue dans les tuiles
 */
extern void display_normal_grid(grid g);

/**
 * \Affiche en console la grille sans les cases, juste les valeurs des cases sur une ligne
 */
extern void light_display_grid(grid g);

#endif


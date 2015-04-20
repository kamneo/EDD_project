#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "utilities.h"

/*
 * \Calcule (valeur_tile)^2
 * \paramètre t, la tuile à calculer
 * \retourne la puissance de la tuile si t>0 ou retourne 0
 */
static unsigned long int pow_of_2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

/*
 * \Fait les additions entre les tuiles d'une ligne
 * \paramètre g, la grille
 * \paramètre i, la ligne de la grille où les additions vont s'effectuer
 * \paramètre debut, 0 si c'est un mouvement vers la gauche, GRID_SIDE - 1 si c'est un mouvement vers la droite
 * \paramètre fin GRID_SIDE - 1 si c'est un mouvement vers la gauche, 0  si c'est un mouvement vers la droite
 * \retoure la valeur à ajouter au score
 */
static unsigned long int add_ligne(grid g, int i, int debut, int fin, int facteur) 
{
	int pos = -1;					// position de la dernière tuile non nulle
	tile empty_tile = 0; 			// tuile par défaut
	tile val = -1;					// valeur de la tuile précédente
	unsigned long int to_add = 0;	// valeur a ajouter au score

	for (int j =  debut; j * facteur < fin; j += 1 * facteur) 
	{
		if (get_tile (g, i, j)!=0)
		{
			//fait l'addition des deux tuiles et remplace la seconde par la tuile par défaut
			if(val == get_tile (g, i, j))
			{
				set_tile (g, i, pos, get_tile (g, i, pos)+1);
				set_tile (g, i, j, empty_tile);
				to_add += pow_of_2(get_tile (g, i, pos));
				pos=-1;
				val=-1;
			}
			// sauvegarde la tuile précédente
			if (val != get_tile (g, i, j))
			{
				val=get_tile (g, i, j);
				pos=j;
			}
		}
	}
	// retourne la valeur à ajouter au score
	return to_add;
}

/*
 * \Fait les additions entre les tuiles d'une colonne
 * \paramètre g, la grille
 * \paramètre j, la colonne où les additions vont s'effectuer
 * \paramètre debut 0 si c'est un mouvement vers le haut, GRID_SIDE - 1 si c'est un mouvement vers le bas
 * \paramètre fin GRID_SIDE - 1 si c'est un mouvement vers le haut, 0 si c'est un mouvement vers le bas
 * \paramètre facteur -1 si c'est un mouvement vers le haut, 1 si c'est un mouvement vers le bas
 * \retourne la valeur à ajouter au score
 */
static unsigned long int add_column(grid g, int j, int debut, int fin, int facteur){
	int pos = -1;					// position de la dernière tuile non nulle
	tile empty_tile = 0; 			// tuile par défaut
	tile val = -1;					// valeur de la tuile précédente
	unsigned long int to_add = 0;	// valeur à ajouter au score

	for (int i =  debut; i * facteur < fin; i += 1 * facteur) 
	{
		if (get_tile (g, i, j)!=0)
		{
			// fait l'addition des deux tuiles et remplace la seconde par la tuile par défaut
			if(val == get_tile (g, i, j))
			{
				set_tile (g, pos, j, get_tile (g, pos, j)+1);
				set_tile (g, i, j, empty_tile);
				to_add += pow_of_2(get_tile (g, pos, j));
				pos=-1;
				val=-1;
			}
			// sauvegarde la tuile précédente
			if (val != get_tile (g, i, j))
			{
				val= get_tile (g, i, j);
				pos=i;
			}
		}
	}

	return to_add;
}

/*
 * \Concatène chaque tuile non nulle sur la gauche de la grille pour un mouvement vers la gauche ou sur la droite pour un mouvement vers la droite
 * \paramètre g, la grille
 * \paramètre i la ligne où l'opération s'effectue
 * \paramètre debut, 0 si c'est un mouvement vers la gauche, GRID_SIDE - 1 si c'est un mouvement vers la droite
 * \paramètre fin GRID_SIDE - 1 si c'est un mouvement vers la gauche, 0  si c'est un mouvement vers la droite
 * \paramètre facteur -1 si c'est un mouvement vers la gauche, 1 si vers la droite
 */
static void concat_ligne(grid g, int i, int debut, int fin, int facteur)
{
	tile empty_tile = 0;
	int nbVide=0;

	for (int j =  debut; j * facteur < fin; j += 1 * facteur) 
	{
		if (get_tile (g, i, j)==0)
			nbVide=nbVide+1;
		if (get_tile (g, i, j)!=0 && nbVide!=0)
		{
			set_tile(g, i, j - (nbVide * facteur), get_tile (g, i, j));
			set_tile (g, i, j, empty_tile);
		}
	}
}

/*
 *Concatène chaque tuile non nulle sur le haut de la grille pour un mouvement vers le haut ou sur le bas pour un mouvement vers le bas
 * \paramètre g, la grille
 * \paramètre j, la colonne où les additions vont s'effectuer
 * \paramètre debut 0 si c'est un mouvement vers le haut, GRID_SIDE - 1 si c'est un mouvement vers le bas
 * \paramètre fin GRID_SIDE - 1 si c'est un mouvement vers le haut, 0 si c'est un mouvement vers le bas
 * \paramètre facteur -1 si c'est un mouvement vers le haut, 1 si c'est un mouvement vers le bas
 */
void concat_column(grid g, int j, int debut, int fin, int facteur)
{
	tile empty_tile = 0;
	int nbVide=0;

	for (int i =  debut; i * facteur < fin; i += 1 * facteur) 
	{
		if (get_tile (g, i, j)==0)
			nbVide=nbVide+1;
		if (get_tile (g, i, j)!=0 && nbVide!=0)
		{
			set_tile(g, i - (nbVide * facteur), j, get_tile (g, i, j));
			set_tile (g, i, j, empty_tile);
		}
	}
}

/**
 * \Vérifie si la ligne peut bouger vers la direction
 * \paramètre g, la grille
 * \paramètre i la ligne en question
 * \paramètre debut, le premier indice 0 si la direction est gauche, GRID_SIZE - 1 si la direction est droite
 * \paramètre fin, le dernier indice 0 si la direction est droite, GRID_SIZE - 1  si la direction est gauche
 * \paramètre facteur -1 si c'est un mouvement vers la gauche, 1 si vers la droite
 * \retourne vrai si la ligne peut bouger, faux sinon
 */
bool lign_can_move(grid g, int i, int debut, int fin, int facteur){
	tile pre = 0;
	bool tile_free = false;

	for (int j =  debut; j * facteur < fin; j += 1 * facteur) {
		// Si on est pas sur la première tuile et que le précédent == la tuile courante
		// on retourne vrai
		// exemple :|2	|3	|1	|1	| est vrai
		if(pre != 0 && pre == get_tile (g, i, j))
			return true;
		//si la tuile courante et vide on met tile_free à vrai
		if(get_tile (g, i, j) == 0)
			tile_free = true;

		// si il y a une tuile libre avant et que le tuile courantz n'est pas null on retourne vrai
		// exemple :|0	|1	|0	|0	| est vrai
		if(tile_free && get_tile (g, i, j) != 0)
			return true;

		pre = get_tile (g, i, j);
	}
	return false;
}

/**
 * \Vérifie si la colonne peut bouger dvers la direction
 * \paramètre g, la grille
 * \paramètre j, la colonne en question
 * \param debut le premier indice, 0 si la direction est haut GRID_SIZE - 1 si la direction est bas
 * \param fin le dernier indice 0 if the direction is RIGHT and GRID_SIZE - 1 if the direction is LEFT
 * \param facteur it's the variable needed for increment if the direction is RIGHT or increment
 * \return if the column can move or not
 */
bool column_can_move(grid g, int j, int debut, int fin, int facteur){
	tile pre = 0;
	bool tile_free = false;

	for (int i =  debut; i * facteur < fin; i += 1 * facteur) {
		// Si on est pas sur la première tuile et que le précédent == la tuile courante
		// on retourne vrai
		// exemple :|2	|3	|1	|1	| est vrai
		if(pre != 0 && pre == get_tile (g, i, j))
			return true;
		//si la tuile courante est vide on met tile_free à vrai
		if(get_tile (g, i, j) == 0)
			tile_free = true;

		// si il y a une tuile libre avant et que la tuile courante n'est pas null on retourne vrai
		// exemple :|0	|1	|0	|0	| est vrai
		if(tile_free && get_tile (g, i, j) != 0)
			return true;

		pre = get_tile (g, i, j);
	}

	return false;
}

/**
 * \Fait le mouvement sur une ligne de la grille
 * \paramètre g, la grille
 * \paramètre i, la ligne en question
 * \paramètre d  la direction
 */
unsigned long int lign_do_move(grid g, int i, dir d)
{
	unsigned long int to_add = 0;

	switch(d)
	{
		case LEFT:
			to_add = add_ligne( g, i, 0, GRID_SIDE, 1);
			concat_ligne( g, i, 0, GRID_SIDE, 1);
			break;
		case RIGHT:
			to_add = add_ligne( g, i, GRID_SIDE -1, 1, -1);
			concat_ligne( g, i, GRID_SIDE -1, 1, -1);
			break;
		default:
			break;
	}

	return to_add;
}

/**
 * \Fait le mouvement sur une colonne de la grille
 * \paramètre g, la grille
 * \paramètre j, la ligne en question
 * \paramètre d  la direction
 */
unsigned long int column_do_move(grid g, int j, dir d)
{
	unsigned long int to_add = 0;

	switch(d)
	{
		case UP:
			to_add = add_column( g, j, 0, GRID_SIDE, 1);
			concat_column( g,j, 0, GRID_SIDE, 1);
			break;
		case DOWN:
			to_add = add_column( g, j, GRID_SIDE -1, 1, -1);
			concat_column( g, j, GRID_SIDE -1, 1, -1);
			break;
		default:
			break;
	}

	return to_add;
}
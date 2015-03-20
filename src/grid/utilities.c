#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "utilities.h"

/*
 * \brief Calculate the pow of the tile
 * \param t the tile to be calculate
 * \return the pow of the tile if t > 0 or return 0
 */
static unsigned long int pow_of_2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

/*
 * \brief Do the additions between tiles on one ligne
 * \param g grid
 * \param i the line where the operations will makes
 * \param debut 0 if is a left movement GRID_SIDE - 1 if is a RIGHT movement (do anithing else)
 * \param fin GRID_SIDE - 1 if is a left movement 0 if is a RIGHT movement (do anithing else)
 * \param facteur -1 if is a left movement and 1 if is a right movment
 * \return value to add at the score
 */
static unsigned long int add_ligne(grid g, int i, int debut, int fin, int facteur) 
{
	int pos = -1;					// position de le dernier tile non nulle
	tile empty_tile = 0; 			// default tile
	tile val = -1;					// valeur de la tile précedente
	unsigned long int to_add = 0;	// valeur a ajouter au score

	for (int j =  debut; j * facteur < fin; j += 1 * facteur) 
	{
		if (get_tile (g, i, j)!=0)
		{
			//fait l'addition des deux tiles et remplace la seconde par la tile par défaut
			if(val == get_tile (g, i, j))
			{
				set_tile (g, i, pos, get_tile (g, i, pos)+1);
				set_tile (g, i, j, empty_tile);
				to_add += pow_of_2(get_tile (g, i, pos));
				pos=-1;
				val=-1;
			}
			// sauvegarde la tile précedente
			if (val != get_tile (g, i, j))
			{
				val=get_tile (g, i, j);
				pos=j;
			}
		}
	}
	// retourne la valeur a ajouter au score
	return to_add;
}

/*
 * \brief Do the additions between tiles on one column
 * \param g grid
 * \param j the column where the operations will makes
 * \param debut 0 if is a up movement GRID_SIDE - 1 if is a down movement (do anithing else)
 * \param fin GRID_SIDE - 1 if is a up movement 0 if is a down movement (do anithing else)
 * \param facteur -1 if is a up movement and 1 if is a down movment
 * \return value to add at the score
 */
static unsigned long int add_column(grid g, int j, int debut, int fin, int facteur){
	int pos = -1;					// position de le dernier tile non nulle
	tile empty_tile = 0; 			// default tile
	tile val = -1;					// valeur de la tile précedente
	unsigned long int to_add = 0;	// valeur a ajouter au score

	for (int i =  debut; i * facteur < fin; i += 1 * facteur) 
	{
		if (get_tile (g, i, j)!=0)
		{
			// fait l'addition des deux tiles et remplace la seconde par la tile par défaut
			if(val == get_tile (g, i, j))
			{
				set_tile (g, pos, j, get_tile (g, pos, j)+1);
				set_tile (g, i, j, empty_tile);
				to_add += pow_of_2(get_tile (g, pos, j));
				pos=-1;
				val=-1;
			}
			// sauvegarde de la premiere derniere tile non nulle
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
 * \brief concat each tile not null on the left of the grid for a left mouvement or right for 
 *        the right mouvement (Do anithing else for a different direction)
 * \param g grid
 * \param i the line where the operations will makes
 * \param debut 0 if is a left movement GRID_SIDE - 1 if is a RIGHT movement (do anithing else)
 * \param fin GRID_SIDE - 1 if is a left movement 0 if is a RIGHT movement (do anithing else)
 * \param facteur -1 if is a left movement and 1 if is a right movment
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
 * \brief concat each tile not null on the top of the grid for a up mouvement or top for 
 *        the down mouvement (Do anithing else for a different direction)
 * \param g grid
 * \param j the column where the operations will makes
 * \param debut 0 if is a up movement GRID_SIDE - 1 if is a down movement (do anithing else)
 * \param fin GRID_SIDE - 1 if is a up movement 0 if is a down movement (do anithing else)
 * \param facteur -1 if is a up movement and 1 if is a down movment
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
 * \brief verify if the lign can move in the direction
 * \param g the grid
 * \param i the curent lign
 * \param debut the first indice worked 0 if the direction is LEFT and GRID_SIZE - 1 if the direction is RIGHT
 * \param fin the last indice worked 0 if the direction is RIGHT and GRID_SIZE - 1 if the direction is LEFT
 * \param facteur it's the variable needed for increment if the direction is RIGHT or increment
 * \return if the lign can move or not
 */
bool lign_can_move(grid g, int i, int debut, int fin, int facteur){
	tile pre = 0;
	bool tile_free = false;

	for (int j =  debut; j * facteur < fin; j += 1 * facteur) {
		// Si on est pas sur la premiere tile et que le precedant == le tile courant
		// on retourne vrai
		// exemple :|2	|3	|1	|1	| est vrai
		if(pre != 0 && pre == get_tile (g, i, j))
			return true;
		//si le tile courant et vide on met tile free a vrai
		if(get_tile (g, i, j) == 0)
			tile_free = true;

		// si il y a un tile free avant et que le tile courant n'est pas null
		// exemple :|0	|1	|0	|0	| est vrai
		if(tile_free && get_tile (g, i, j) != 0)
			return true;

		pre = get_tile (g, i, j);
	}
	return false;
}

/**
 * \brief verify if the column can move in the direction
 * \param g the grid
 * \param j the curent column
 * \param debut the first indice worked 0 if the direction is LEFT and GRID_SIZE - 1 if the direction is DOWN
 * \param fin the last indice worked 0 if the direction is RIGHT and GRID_SIZE - 1 if the direction is LEFT
 * \param facteur it's the variable needed for increment if the direction is RIGHT or increment
 * \return if the column can move or not
 */
bool column_can_move(grid g, int j, int debut, int fin, int facteur){
	tile pre = 0;
	bool tile_free = false;

	for (int i =  debut; i * facteur < fin; i += 1 * facteur) {
		// Si on est pas sur la premiere tile et que le precedant == le tile courant
		// on retourne vrai
		// exemple :|2	|3	|1	|1	| est vrai
		if(pre != 0 && pre == get_tile (g, i, j))
			return true;
		//si le tile courant et vide on met tile free a vrai
		if(get_tile (g, i, j) == 0)
			tile_free = true;

		// si il y a un tile free avant et que le tile courant n'est pas null
		// exemple :|0	|1	|0	|0	| est vrai
		if(tile_free && get_tile (g, i, j) != 0)
			return true;

		pre = get_tile (g, i, j);
	}

	return false;
}

/**
 * \brief do the move on a line in the grid 
 * \param g the grid
 * \param i the curent line
 * \param d the direction on the line (LEFT or RIGHt any else do nothing)
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
 * \brief do the move on a column in the grid 
 * \param g the grid
 * \param i the curent column
 * \param d the direction on the column (UP or DOWN any else do nothing)
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
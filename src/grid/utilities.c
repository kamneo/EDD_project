#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "utilities.h"

static void add_score(grid g, unsigned long int x){
	set_score(g, grid_score (g) + x);
}

static unsigned long int puissanceDe2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

bool lign_can_move(grid g, int i, int debut, int fin, int facteur){
	tile pre = 0;
	bool tile_free = false;

	if(facteur == -1)
		fin += 1;

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

bool colon_can_move(grid g, int j, int debut, int fin, int facteur){
	tile pre = 0;
	bool tile_free = false;

	if(facteur == -1)
		fin += 1;

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

static void add_ligne(grid g, int i, int debut, int fin, int facteur) 
{
	int pos = -1;
	tile empty_tile = 0;
	unsigned long int s=0;
	tile val = -1;

	if(facteur == -1)
		fin += 1;

	for (int j =  debut; j * facteur < fin; j += 1 * facteur) 
	{
		if (get_tile (g, i, j)!=0)
		{
			if(val == get_tile (g, i, j))
			{
				set_tile (g, i, pos, get_tile (g, i, pos)+1);
				set_tile (g, i, j, empty_tile);
				s=puissanceDe2(get_tile (g, i, pos));
				add_score(g,s);
				pos=-1;
				val=-1;
			}
			if (val != get_tile (g, i, j))
			{
				val=get_tile (g, i, j);
				pos=j;
			}
		}
	}
}

static void add_colon(grid g, int j, int debut, int fin, int facteur){
	unsigned long int s=0;
	int pos = -1;
	tile empty_tile = 0;
	tile val = -1;

	if(facteur == -1)
		fin += 1;

	for (int i =  debut; i * facteur < fin; i += 1 * facteur) 
	{
		if (get_tile (g, i, j)!=0)
		{
			if(val == get_tile (g, i, j))
			{
				set_tile (g, pos, j, get_tile (g, pos, j)+1);
				set_tile (g, i, j, empty_tile);
				s=puissanceDe2(get_tile (g, pos, j));
				add_score(g,s);
				pos=-1;
				val=-1;
			}
			if (val != get_tile (g, i, j))
			{
				val= get_tile (g, i, j);
				pos=i;
			}
		}
	}
}

static void concat_ligne(grid g, int i, int debut, int fin, int facteur)
{
	tile empty_tile = 0;
	int nbVide=0;

	if(facteur == -1)
		fin += 1;

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

void concat_colon(grid g, int j, int debut, int fin, int facteur)
{
	tile empty_tile = 0;
	int nbVide=0;

	if(facteur == -1)
		fin += 1;

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


void lign_do_move(grid g, int i, dir d)
{
	switch(d)
	{
		case LEFT:
			add_ligne( g, i, 0, GRID_SIDE, 1);
			concat_ligne( g, i, 0, GRID_SIDE, 1);
			break;
		case RIGHT:
			add_ligne( g, i, GRID_SIDE -1, 0, -1);
			concat_ligne( g, i, GRID_SIDE -1, 0, -1);
			break;
		default:
			break;
	}
}

void colon_do_move(grid g, int j, dir d)
{
	switch(d)
	{
		case UP:
			add_colon( g, j, 0, GRID_SIDE, 1);
			concat_colon( g,j, 0, GRID_SIDE, 1);
			break;
		case DOWN:
			add_colon( g, j, GRID_SIDE -1, 0, -1);
			concat_colon( g, j, GRID_SIDE -1, 0, -1);
			break;
		default:
			break;
	}
}
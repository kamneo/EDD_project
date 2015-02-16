#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "utilities.h"

void add_score(grid g, unsigned long int x){
	set_score(g, grid_score (g) + x);
}

unsigned long int puissanceDe2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

bool lign_can_move(grid g, int i, dir d, int debut, int fin, int facteur){
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

bool colon_can_move(grid g, int j, dir d, int debut, int fin, int facteur){
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

void add_ligne(grid g, int i,dir d) 
{
	int pos = -1;
	tile empty_tile = 0;
	unsigned long int s=0;
	tile val = -1;
	switch(d)
	{
		case LEFT:
			for (int j = 0; j < GRID_SIDE; j++)
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
			break;
		case RIGHT:
			for (int j = GRID_SIDE-1; j >= 0; j--)
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
			break;
		default:
			break;
	}
	return;
}


void add_colon(grid g, int j,dir d) 
{
	unsigned long int s=0;
	int pos = -1;
	tile empty_tile = 0;
	tile val = -1;
	switch(d)
	{
		case UP:
			for (int i = 0; i < GRID_SIDE; i++)
			{
				if (get_tile (g, i, j)!=0)
				{
					if( val == get_tile (g, i, j))
					{
						set_tile (g, pos, j, get_tile (g, pos, j)+1);
						set_tile (g, i, j, empty_tile);
						s=puissanceDe2(get_tile (g, pos, j));
						add_score(g,s);
						pos=-1;
						val=-1;
					}
					if ( val != get_tile (g, i, j))
					{
						val= get_tile (g, i, j);
						pos=i;
					}
				}
			}
			break;
		case DOWN:
			for (int i = GRID_SIDE-1; i >= 0; i--)
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
			break;
		default:
			break;
	}
	return;
}


void concat_ligne(grid g, int i,dir d)
{
	tile empty_tile = 0;
	int nbVide=0;
	switch(d)
	{
		case LEFT:
			for (int j = 0; j < GRID_SIDE; j++)
			{
				if (get_tile (g, i, j)==0)
					nbVide=nbVide+1;
				if (get_tile (g, i, j)!=0 && nbVide!=0)
				{
					set_tile(g, i, j - nbVide, get_tile (g, i, j));
					set_tile (g, i, j, empty_tile);
				}
			}
			break;
		case RIGHT:
			for (int j = GRID_SIDE-1; j >= 0; j--)
			{
				if (get_tile (g, i, j)==0)
					nbVide=nbVide+1;
				if (get_tile (g, i, j)!=0 && nbVide!=0)
				{
					set_tile(g, i, j + nbVide, get_tile (g, i, j));
					set_tile (g, i, j, empty_tile);
				}
			}
			break;
		default:
			break;
	}
	return;
}

void concat_colon(grid g, int j ,dir d)
{
	tile empty_tile = 0;
	int nbVide=0;
	switch(d)
	{
		case UP:
			for (int i = 0; i < GRID_SIDE; i++)
			{
				if (get_tile (g, i, j)==0)
					nbVide=nbVide+1;
				if (get_tile (g, i, j)!=0 && nbVide!=0)
				{
					set_tile(g, i - nbVide, j, get_tile (g, i, j));
					set_tile (g, i, j, empty_tile);
				}
			}
			break;
		case DOWN:
			for (int i = GRID_SIDE-1; i >= 0; i--)
			{
				if (get_tile (g, i, j)==0)
					nbVide=nbVide+1;
				if (get_tile (g, i, j)!=0 && nbVide!=0)
				{
					set_tile(g, i + nbVide, j, get_tile (g, i, j));
					set_tile (g, i, j, empty_tile);
				}
			}
			break;
		default:
			break;
	}
	return;
}


void lign_do_move(grid g, int i, dir d)
{
	switch(d)
	{
		case LEFT:
			add_ligne( g, i, d);
			concat_ligne( g,i,d);
			break;

		case RIGHT:
			add_ligne( g, i, d);
			concat_ligne( g,i,d);
			break;
		default:
			break;
	}
}

void colon_do_move(grid g, int i, dir d)
{
	switch(d)
	{
		case UP:
			add_colon( g, i, d);
			concat_colon( g,i,d);
			break;

		case DOWN:
			add_colon( g, i, d);
			concat_colon( g,i,d);
			break;
		default:
			break;
	}
}
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct grid_s{
    tile** tiles;
    unsigned long int score;
};


static unsigned long int puissanceDe2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

static bool lign_can_move(grid g, int i, dir d){
	tile pre = 0;
	bool tile_free = false;
	switch(d)
	{
		case LEFT:
			for (int j =  0; j < GRID_SIDE; j++) {
				// Si on est pas sur la premiere tile et que le precedant == le tile courant
				// on retourne vrai
				// exemple :|2	|3	|1	|1	| est vrai
				if(pre != 0 && pre == g->tiles[i][j])
					return true;
				//si le tile courant et vide on met tile free a vrai
				if(g->tiles[i][j] == 0)
					tile_free = true;

				// si il y a un tile free avant et que le tile courant n'est pas null
				// exemple :|0	|1	|0	|0	| est vrai
				if(tile_free && g->tiles[i][j] != 0)
					return true;

				pre = g->tiles[i][j];
			}
			break;
		case RIGHT:
			for (int j = GRID_SIDE - 1; j >= 0; j--) {
				// Si on est pas sur la premiere tile et que le precedant == le tile courant
				// on retourne vrai
				// exemple :|2	|3	|1	|1	| est vrai
				if(pre != 0 && pre == g->tiles[i][j])
					return true;
				//si le tile courant et vide on met tile free a vrai
				if(g->tiles[i][j] == 0)
					tile_free = true;

				// si il y a un tile free avant et que le tile courant n'est pas null
				// exemple :|1	|0	|0	|0	| est vrai
				if(tile_free && g->tiles[i][j] != 0)
					return true;

				pre = g->tiles[i][j];
			}
			break;
		default:
			return false;
	}
	return false;
}

static bool colon_can_move(grid g, int j, dir d){
	tile pre = 0;
	bool tile_free = false;
	switch(d)
	{
		case UP:
			for (int i =  0; i < GRID_SIDE; i++) {
				// Si on est pas sur la premiere tile et que le precedant == le tile courant
				// on retourne vrai
				// exemple :|2	|3	|1	|1	| est vrai
				if(pre != 0 && pre == g->tiles[i][j])
					return true;
				//si le tile courant et vide on met tile free a vrai
				if(g->tiles[i][j] == 0)
					tile_free = true;

				// si il y a un tile free avant et que le tile courant n'est pas null
				// exemple :|0	|1	|0	|0	| est vrai
				if(tile_free && g->tiles[i][j] != 0)
					return true;

				pre = g->tiles[i][j];
			}
			break;
		case DOWN:
			for (int i = GRID_SIDE - 1; i >= 0; i--) {
				// Si on est pas sur la premiere tile et que le precedant == le tile courant
				// on retourne vrai
				// exemple :|2	|3	|1	|1	| est vrai
				if(pre != 0 && pre == g->tiles[i][j])
					return true;
				//si le tile courant et vide on met tile free a vrai
				if(g->tiles[i][j] == 0)
					tile_free = true;

				// si il y a un tile free avant et que le tile courant n'est pas null
				// exemple :|1	|0	|0	|0	| est vrai
				if(tile_free && g->tiles[i][j] != 0)
					return true;

				pre = g->tiles[i][j];
			}
			break;
		default:
			return false;
	}
	return false;
}

static void lign_do_move(grid g, int i, dir d)
{
	tile empty_tile = 0;
	bool tile_free = false;
	tile pre = 0;
	int j2;
				printf("\n");

	switch(d)
	{
		case LEFT:
			j2 = 0;
			for (int j = 0; j < GRID_SIDE; j++)
			{
				printf("%d", j2);
				if(g->tiles[i][j] != 0 ){
					if(g->tiles[i][j] == pre){
						set_tile(g, i, j2, g->tiles[i][j] + pre);
						set_tile(g, i, j, empty_tile);
						pre = g->tiles[i][j];
					}else{
						set_tile(g, i, j2 + 1, g->tiles[i][j]);
						set_tile(g, i, j, empty_tile);
					}
				}else{
					tile_free = true;
				}
			}
			break;
		case RIGHT:
			break;
		default:
			break;
	}
}

static void colon_do_move(grid g, int i, dir d)
{
	
}

/**
 * \brief Initialize grid structure
 * \return created an empty grid with score equal to 0
 */
grid new_grid ()
{
	grid g;
	g = malloc(sizeof(struct grid_s));
	g->tiles = malloc(sizeof(tile) * GRID_SIDE);
	for(int i = 0; i < GRID_SIDE; i++)
            g->tiles[i] = malloc(sizeof(tile) * GRID_SIDE);


	for(int i = 0; i < GRID_SIDE; i++)
        for(int j = 0; j < GRID_SIDE; j++)
            g->tiles[i][j] = 0;
	return g;
}

/**
 * \brief Destroy the grid and free allocated memory
 * \param g the grid to destroy
 */
void delete_grid (grid g)
{
	for(int i = 0; i < GRID_SIDE; i++)
		free (g->tiles[i]);
	free (g->tiles);
	free(g);
}

/**
 * \brief Clone the grid
 * \param src the grid to copy
 * \param dst the copied grid
 */
void copy_grid (grid src, grid dst)
{
	for(int i = 0; i < GRID_SIDE; i++)
        for(int j = 0; j < GRID_SIDE; j++)
            dst->tiles[i][j] = src->tiles[i][j];

    dst->score = src->score;
}

/**
 * \brief Get game's score
 * \param g the grid
 * \return the computed score during the game
 */
unsigned long int grid_score (grid g)
{
	return g->score;
}


/**
 * \brief Get tile  (log_2-encoded) from the grid by specifying his coordinates
 * \param g the grid
 * \param x and y tile's coordinates
 * \return the tile
 * \pre 0 <= x < GRID_SIDE and 0 <= y < GRID_SIDE
 */
tile get_tile (grid g, int x, int y)
{
    return g->tiles[x][y];
}

/**
 * \brief Change tile's value
 * \param g the grid
 * \param x and y tile's coordinates
 * \param t new tile's value
 */
void set_tile (grid g, int x, int y, tile t)
{
	g->tiles[x][y] = t;
}

/**
 * \brief Verify if a given movement is possible
 * \param g the grid
 * \param d movement's direction
 * \return true if the movement is possible, false else
 */
bool can_move (grid g, dir d)
{
	if( d == LEFT || d == RIGHT)
	{
		for (int i = 0; i < GRID_SIDE; i++)
		{
			if(lign_can_move(g, i, d))
				return true;
		}
	}

	if( d == UP || d == DOWN)
	{
		for (int j = 0; j < GRID_SIDE; j++)
		{
			if(colon_can_move(g, j, d))
				return true;
		}
	}

	return false;
}

/**
 * \brief Verify game's status, if no more movement is possible the game is over
 * \param g the grid
 * \return true if there is no more possible movements, false else
 */
bool game_over (grid g);

/**
 * \brief Move every tiles of the grid in the direction specified by the user
 * \param g the grid
 * \param d the chosen direction
 * \pre the movement d must be possible (i.e. can_move(g,d) == true).
 */
void do_move (grid g, dir d)
{
	if(!can_move(g, d))
	{
		printf("Erreur: movement impossible !\n");
		return;
	}

	if( d == LEFT || d == RIGHT)
	{
		for (int i = 0; i < GRID_SIDE; i++)
		{
			lign_do_move(g, i, d);
		}
	}

	if( d == UP || d == DOWN)
	{
		for (int j = 0; j < GRID_SIDE; j++)
		{
			colon_do_move(g, j, d);
		}
	}

}

/**
 * \brief Randomly add a tile in the grid in a free space when a movement is finished.
 * With probability 9/10 the new tile has value 2 and with probability 1/10 the new tile has value 4.
 * \param g the grid
 * \pre grid g must contain  at least one empty tile.
 */
void add_tile (grid g);

/**
 * \brief Play a direction in the grid.
 * \param g the grid
 * \param d the direction
 * \pre the movement d must be possible (i.e. can_move(g,d) == true).
 */

void play (grid g, dir d);

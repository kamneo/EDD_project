#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "grid.h"
#include "utilities.h"

#define SENS_NEGATIF -1
#define SENS_POSITIF 1

struct grid_s{
    tile** tiles;
    unsigned long int score;
};

/*
 * \brief Calculate an random int beetween 0 and n
 * \param n Indice max
 * \return a random int beetween 0 and n
 */
static int rang_aleatoire (int n){
	return rand()%n;
}

/*
 * \brief Calculate a value, this value have 9/10 chance to be 1 and 1/10 to be 2
 * \return an int between 1 and 2
 */
static int valeur_aleatoire (){
	if (rand()%10 < 9)
		return 1;
	else
		return 2;
}

/*
 * \brief Initialize grid structure
 * \return created an empty grid with score equal to 0
 */
grid new_grid ()
{
	// initialisation de la srand() qui gère la génération des nombres aléatoires
	srand(time(NULL));
	grid g;
	g = malloc(sizeof(struct grid_s));
	g->tiles = malloc(sizeof(void *) * GRID_SIDE);
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
 * \brief Set game's score
 * \param x the new score
 */
void set_score(grid g, unsigned long int x)
{
	g->score = x;
}


/**
 * \brief Get tile  (log_2-encoded) from the grid by specifying his coordinates
 * \param g the grid
 * \param x and y tile's coordinates
 * \return the tile
 * \pre 0 < = x < GRID_SIDE and 0 < = y < GRID_SIDE
 */

tile get_tile (grid g, int x, int y){
	return (g->tiles[x][y]);
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
	switch(d)
	{
		case LEFT:
			for (int i = 0; i < GRID_SIDE; i++)
			{
				// ici on parcourt la grille de l'indice 0 à la taille du tableau pour chaque ligne
				if(lign_can_move(g, i, 0, GRID_SIDE, SENS_POSITIF))
					return true;
			}
			break;
		case RIGHT:
			for (int i = 0; i < GRID_SIDE; i++)
			{
				// ici on parcourt la grille de l'indice la taille du tableau - 1 à 1 pour chaque ligne
				if(lign_can_move(g, i, GRID_SIDE -1 , 1, SENS_NEGATIF))
					return true;
			}
			break;
		case UP:
			for (int i = 0; i < GRID_SIDE; i++)
			{
				// ici on parcourt la grille de l'indice 0 à la taille du tableau pour chaque colonne
				if(colon_can_move(g, i, 0, GRID_SIDE, SENS_POSITIF))
					return true;
			}
			break;
		case DOWN:
			for (int i = 0; i < GRID_SIDE; i++)
			{
				// ici on parcourt la grille de l'indice la taille du tableau - 1 à 1 pour chaque colonne
				if(colon_can_move(g, i, GRID_SIDE -1 , 1, SENS_NEGATIF))
					return true;
			}
			break;
		default:
			return false;
	}

	return false;
}

/**
 * \brief Verify game's status, if no more movement is possible the game is over
 * \param g the grid
 * \return true if there is no more possible movements, false else
 */
bool game_over (grid g)
{
	return !can_move(g, LEFT) && !can_move(g, RIGHT) && !can_move(g, UP) && !can_move(g, DOWN);
}

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

	// en fonction de la direction passée en parametre, on fait un movement ligne à ligne ou colonne à colonne.
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
void add_tile (grid g){
	int taille = (GRID_SIDE*GRID_SIDE)*2; // taille maximale de notre tableau
	int nbFree = 0; // nombre de tile libre
	int* tab; // le tableau de coordonée
	int nombreAleatoire;

	tab = malloc(sizeof(int)*taille);
	// on parcourt la grille
	for (int i = 0; i < GRID_SIDE; i++){
		for (int j = 0; j < GRID_SIDE; j++)
		{
			// si la tile à la position i et j est vide on ajoute au tableau tab les valeurs de i et j
			if (g->tiles[i][j] == 0)
			{
				tab[nbFree*2] = i;
				tab[nbFree*2+1] = j;
				nbFree += 1;
			}		
		}
	}

	if (nbFree == 0){
		printf("Erreur il n'y a plus de case libre !\n");
		return;
	}

	// on génére un nombre aléatoire pour obtenir les coordonées dans le tableau tab d'une tile vide
	nombreAleatoire = rang_aleatoire(nbFree)*2;
	// au tile obtenue on change sa valeur entre 1 et 2 (9/10 chance d'avoir 1 et 1/10 chance d'avoir 2)
	g->tiles[tab[nombreAleatoire]][tab[nombreAleatoire+1]] = valeur_aleatoire();
	free(tab);
}

/**
 * \brief Play a direction in the grid.
 * \param g the grid
 * \param d the direction
 * \pre the movement d must be possible (i.e. can_move(g,d) == true).
 */
void play (grid g, dir d)
{	
	if(!can_move(g, d))
	{
		printf("Erreur: movement impossible !\n");
		return;
	}

	// on fait le movement sur la grille
	do_move(g, d);

	// on ajoute une tile à une position aléatoire
	add_tile(g);
}
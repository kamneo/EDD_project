#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"

/*
 * \brief Calculate the pow of the tile
 * \param t the tile to be calculate
 * \return the pow of the tile if t > 0 or return 0
 */
static unsigned long int puissanceDe2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

/**
 * \brief Display in console the grid with color and the pow of value contained in tile
 */
void display_grid(grid g)
{

	for(int i = 0; i < GRID_SIDE * 2 +1; i++)
    {
	    if(i % 2 == 0)
	    	if (i != 0)
	    		printf("|\n+");
	    	else
	    		printf("+");
	    else
	    	printf("\n");

	    for(int j = 0; j < GRID_SIDE; j++)
	    	if(i % 2 != 0)
	    	{
	    		unsigned long int s = puissanceDe2(get_tile(g, i/2, j));
	    		if(s == 0)
	    			printf("| \t");
	    		else
	        		printf("|\x1B[48;5;%dm%lu\t\033[0m", get_tile(g, i/2, j)%10 + 1, s);
	        }
	        else {
	        	printf("-------+");
	        }
    }

	printf("\n le score est de : %lu \n\n",grid_score(g));
}

/**
 * \brief Display in console the grid with color and the value contained in tile
 */
void display_normal_grid(grid g)
{

	for(int i = 0; i < GRID_SIDE * 2 +1; i++)
    {
	    if(i % 2 == 0)
	    	if (i != 0)
	    		printf("|\n+");
	    	else
	    		printf("+");
	    else
	    	printf("\n");

	    for(int j = 0; j < GRID_SIDE; j++)
	    	if(i % 2 != 0)
	    	{
	        	printf("|\x1B[48;5;%dm%lu\t\033[0m", get_tile(g, i/2, j)%10 + 1, (long unsigned int)(get_tile(g, i/2, j)));
	        }
	        else {
	        	printf("-------+");
	        }
    }

	printf("\n le score est de : %lu \n\n",grid_score(g));
}
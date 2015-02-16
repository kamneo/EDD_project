#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"

static unsigned long int puissanceDe2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

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
	        		printf("|\x1B[48;5;%lum%lu\t\033[0m", s%255, s);
	        }
	        else {
	        	printf("-------+");
	        }
    }

	printf("\n le score est de : %lu \n\n",grid_score(g));
}

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
	        	printf("| %lu \t", (long unsigned int)(get_tile(g, i/2, j)));
	        }
	        else {
	        	printf("-------+");
	        }
    }

	printf("\n le score est de : %lu \n\n",grid_score(g));
}
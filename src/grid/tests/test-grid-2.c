/*
 * Fichier de test du module grid - Test homogénéité add_tile()
 * Ce fichier test la fonction add_tile()
 * principe :
 * On creer N grid et a chaque fois on ajoute une tile. Avec le test de khi2, on admet une erreur de ALPHA.
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <grid.h>
#include <affichage.h>

#define ALPHA 0.05

int main (int argc, char** argv){
 	srand(time(NULL));
	int nbGame=0;
	int** counter;

	// on creer un tableau qui contiendra le nombre de fois que la tile (i, j) sera modifier
	counter = malloc(sizeof(void*) * GRID_SIDE);
	for (int i = 0; i < GRID_SIDE; i++)
	{
		counter[i] = malloc(sizeof(int) * GRID_SIDE);
	}

	for (int i = 0; i < GRID_SIDE; i++)
	{
		for (int j = 0; j < GRID_SIDE; j++)
		{
			counter[i][j] = 0;
		}
	}

	// on jour N partie
	while(nbGame<10000){
		grid g;
		g=new_grid();

		add_tile(g);

		for (int i = 0; i < GRID_SIDE; i++)
		{
			for (int j = 0; j < GRID_SIDE; j++)
			{
				if(get_tile(g, i, j) != 0)
					counter[i][j] += 1;

			}
		}
		
		delete_grid(g);
		nbGame++;
	}

	// application du theoreme de Khi-deux
	double ratio = nbGame/ (GRID_SIDE * GRID_SIDE);
	double probabilite = 0.0;

	for (int i = 0; i < GRID_SIDE; i++)
	{
		for (int j = 0; j < GRID_SIDE; j++)
		{
			probabilite += ((counter[i][j] - ratio) * (counter[i][j] - ratio)) / ratio;
		}

		free(counter[i]);
	}

	free(counter);

	// vérification si le test a échouer ou pas
	if(probabilite >= ratio * ALPHA)
		return EXIT_FAILURE;

	
	printf("test ok !\n");
	return EXIT_SUCCESS;
}

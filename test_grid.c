/*
 * Fichier de test du module grid
 */
 #include <stdlib.h>
 #include <stdio.h>
 #include "grid.h"

 static int main (char** argv, int arc)
 {
    grid g;
    g = new_grid ();

    for(int i = 0; i < GRID_SIDE; i++)
    {
        printf("\n");
        for(int j = 0; j < GRID_SIDE; j++)
            printf("%d \t", get_tile(g, i, j));
    }
    return EXIT_SUCCESS;
 }

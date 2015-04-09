#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <strategy.h>
#include <grid.h>
#include "affichage.h"
#include <unistd.h>

#define NOUVELLE_PARTIE 1
#define MAX_VALUE 12
#define TOUR 1

long int top_chrono;
int verbose = 0; // niveau de debuging

void demarrer_chrono() {
        top_chrono = clock();
}

void stop_chrono() {
        long int arret_chrono = clock();
        fprintf(stderr, "Le calcul a pris %f secondes.\n",
                (float)(arret_chrono - top_chrono) / CLOCKS_PER_SEC);
}

/*
 * MEMOIRE qui contient les scores cumulés des grilles jusqu'a ce que
 * l'utilisateur quitte le programme et le nombre de fois que la valeur max
 * est apparue
 */
typedef struct _memoire {
	int* tab;
	unsigned long int score;
} MEMOIRE;

int end_game(grid g);
int end_game_stat(MEMOIRE m, grid g);
unsigned long int pow_of_2(tile t);

int main(int argc, char *argv[]) {
	// initialisation de time pour la génération aléatoire de tile
	srand(time(NULL));
	MEMOIRE m;
	m.score = 0;
	m.tab = malloc(sizeof(int) * MAX_VALUE);

	bool tour_suivant;		// valeur boolean est a vrai quand on veut recommencer une partie
	dir direction;			// contient la direction décrite dans grid.h
	grid g;					// instance de la grid
	strategy strat;			// instance de la stratégie

	int nb_tour = TOUR;

	printf("1 - affiche la grille à chaque coup\n");
	printf("2 - affiche juste la grille de fin\n");
	int key = getchar();

		demarrer_chrono();

	while (NOUVELLE_PARTIE   && nb_tour != 0) {
		g = new_grid();
		add_tile(g);
		add_tile(g);

		// initialisation de la structure strategy
		strat = A2_bonnet_borde_pinero_basic();

		tour_suivant = true;

		if(key == '1')
			display_grid(g);

		while (tour_suivant) {
			// recherche de la meilleure direction
			direction = strat->play_move(strat, g);

			//sleep(1);

			if(direction != -1)
			{
				// Réalisation du coup dans la direction voulue
				play(g, direction);
			}

			if(key == '1')
				display_grid(g);
			// dans le cas ou la partie est terminée
			while (game_over(g) && tour_suivant) {
				if(key == '2')
					display_grid(g);

				// Ceci ne sert que pour les stats
				m.score += grid_score(g);
				int indice = 0;
				for (int x = 0; x < GRID_SIDE; ++x) {
					for (int y = 0; y < GRID_SIDE; ++y) {
						if (get_tile(g, x, y) > indice) {
							indice = get_tile(g, x, y);
						}
					}
				}
				m.tab[indice] += 1;

				tour_suivant = false;
				nb_tour--;
			}// end game_over
		} // end tour_suivant
	} // end PARTIE_SUIVANTE
	stop_chrono();
	return end_game_stat(m, g);
}

/*
 * \brief close the window created by ncurses & delete the grid
 * \param g the grid
 */
int end_game(grid g) {
	printf("Merci d'avoir joue.\n");
	delete_grid(g);
	return EXIT_SUCCESS;
}

/*
 * \brief close the window created by ncurses & delete the grid & display the statistics
 * \param g the grid
 * \param m Memoire
 */
int end_game_stat(MEMOIRE m, grid g) {
	int total = 0;

	printf("Merci d'avoir joue.\n");
	delete_grid(g);
	printf("score cumule : %lu \n", m.score);
	for (int i = 0; i < MAX_VALUE; ++i) {
		printf("%f = %d\n", pow(2, i), m.tab[i]);
		total += m.tab[i];
	}
	printf("score moyen : %lu \n", m.score / total);

	free(m.tab);
	return EXIT_SUCCESS;
}

/*
 * \brief Calculate the pow of the tile
 * \param t the tile to be calculate
 * \return the pow of the tile if t > 0 or return 0
 */
unsigned long int pow_of_2(tile t) {
	if (t == 0)
		return t;
	return pow(2, t);
}

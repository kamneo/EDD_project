#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <strategy_fast.h>
#include <grid.h>
#include "affichage.h"
#include <unistd.h>

#define NEW_GAME 1
#define MAX_VALUE 12
#define ROUND 1

long int top_chrono;
int verbose = 0; // niveau de debuging

void start_chrono() {
        top_chrono = clock();
}

void stop_chrono() {
        long int end_chrono = clock();
        fprintf(stderr, "Le calcul a pris %f secondes.\n",
                (float)(end_chrono - top_chrono) / CLOCKS_PER_SEC);
}

/*
 * MEMOIRE qui contient les scores cumulés des grilles jusqu'à ce que
 * l'utilisateur quitte le programme et le nombre de fois que la valeur max
 * est apparue
 */
typedef struct _memory {
	int* tab;
	unsigned long int score;
} MEMORY;

int end_game(grid g);
int end_game_stat(MEMORY m, grid g);
unsigned long int pow_of_2(tile t);

int main(int argc, char *argv[]) {
	// initialisation de time pour la génération aléatoire de tile
	srand(time(NULL));
	MEMORY m;
	m.score = 0;
	m.tab = malloc(sizeof(int) * MAX_VALUE);

	bool next_round;		// valeur boolean est a vrai quand on veut recommencer une partie
	dir direction;			// contient la direction décrite dans grid.h
	grid g;					// instance de la grid
	strategy strat;			// instance de la stratégie

	int nb_round = ROUND;

	printf("1 - affiche la grille à chaque coup\n");
	printf("2 - affiche juste la grille de fin\n");
	int key = getchar();

		start_chrono();

	while (NEW_GAME   && nb_round != 0) {
		g = new_grid();
		add_tile(g);
		add_tile(g);

		// initialisation de la structure strategy
		strat = A2_bonnet_borde_pinero_fast();

		next_round = true;

		if(key == '1')
			display_grid(g);

		while (next_round) {
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
			// dans le cas où la partie est terminée
			while (game_over(g) && next_round) {
				if(key == '2')
					display_grid(g);

				// Ceci ne sert que pour les stats
				m.score += grid_score(g);
				int index = 0;
				for (int x = 0; x < GRID_SIDE; ++x) {
					for (int y = 0; y < GRID_SIDE; ++y) {
						if (get_tile(g, x, y) > index) {
							index = get_tile(g, x, y);
						}
					}
				}
				m.tab[index] += 1;

				next_round = false;
				nb_round--;
			}// fin game_over
		} // fin next_round
	} // fin PARTIE_SUIVANTE
	stop_chrono();
	return end_game_stat(m, g);
}

/*
 * \ferme la fenêtre créée par ncurses & supprime la grille
 * \paramètre g, la grille
 */
int end_game(grid g) {
	printf("Merci d'avoir joue.\n");
	delete_grid(g);
	return EXIT_SUCCESS;
}

/*
 * \ferme la fenêtre créée par ncurses & supprime la grille & affiche les statistiques
 * \paramètre g, la grille
 * \paramètre m mémoire
 */
int end_game_stat(MEMORY m, grid g) {
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


unsigned long int pow_of_2(tile t) {
	if (t == 0)
		return t;
	return pow(2, t);
}

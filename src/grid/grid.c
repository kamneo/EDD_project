#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "grid.h"
#include "utilities.h"

#define SENS_NEGATIF -1
#define SENS_POSITIF 1

struct grid_s {
	tile** tiles;
	unsigned long int score;
};

/*
 * \Calcule un int aléatoire entre 0 et n
 * \paramètre n , le max
 * \retourne un entier aléatoire entre 0 et n
 */
static int rang_aleatoire(int n) {
	return rand() % n;
}

/*
 * \Calcule une valeur qui a 9/10 de chances d'être 1 et 1/10 d'êtrre 2
 * \retourne un entier entre 1 et 2
 */
static int valeur_aleatoire() {
	if (rand() % 10 < 9)
		return 1;
	else
		return 2;
}

/*
 * \Initialise la structure de la grille
 * \retourne une grille vide avec un score de 0
 */
grid new_grid() {
	// initialisation de la srand() qui gère la génération des nombres aléatoires
	grid g;
	g = malloc(sizeof(struct grid_s));
	g->tiles = malloc(sizeof(void *) * GRID_SIDE);
	for (int i = 0; i < GRID_SIDE; i++)
		g->tiles[i] = malloc(sizeof(tile) * GRID_SIDE);

	for (int i = 0; i < GRID_SIDE; i++)
		for (int j = 0; j < GRID_SIDE; j++)
			g->tiles[i][j] = 0;

	g->score = 0;
	return g;
}

/**
 * \Détruit la grille et libère la mémoire allouée
 * \paramètre g , la grille à détruire
 */
void delete_grid(grid g) {
	for (int i = 0; i < GRID_SIDE; i++)
		free(g->tiles[i]);
	free(g->tiles);
	free(g);
}

/**
 * \Clone la grille
 * \paramètre src la grille à copier (source)
 * \paramètre dst la grille copiée (destination)
 */
void copy_grid(grid src, grid dst) {
	for (int i = 0; i < GRID_SIDE; i++)
		for (int j = 0; j < GRID_SIDE; j++)
			dst->tiles[i][j] = src->tiles[i][j];

	dst->score = src->score;
}

/**
 * \Obtient le score de la grille
 * \paramètre g, la grille
 * \retourne le score calculé pendant le jeu
 */
unsigned long int grid_score(grid g) {
	return g->score;
}

/**
 * \Obtient une tuile de la grille grâce aux coordonnées spécifiées
 * \paramètre g, la grille
 * \paramètres x et y, les coordonnées de la tile
 * \retourne la tuile
 */
tile get_tile(grid g, int x, int y) {
	return (g->tiles[x][y]);
}

/**
 * \Change la valeure de la tuile
 * \paramètre g, la grille
 * \paramètres x et y, les coordonnées de la tuile
 * \paramètre t, la nouvelle valeur de la tuile
 */
void set_tile(grid g, int x, int y, tile t) {
	g->tiles[x][y] = t;
}

/**
 * \Vérifie si un mouvement donné est possible
 * \paramètre g, la grille
 * \paramètre d, la direction
 * \retourne vrai si le mouvement est possible, faux sinon
 */
bool can_move(grid g, dir d) {
	switch (d) {
	case LEFT:
		for (int i = 0; i < GRID_SIDE; i++) {
			// ici on parcourt la grille de l'indice 0 à la taille du tableau pour chaque ligne
			if (lign_can_move(g, i, 0, GRID_SIDE, SENS_POSITIF))
				return true;
		}
		break;
	case RIGHT:
		for (int i = 0; i < GRID_SIDE; i++) {
			// ici on parcourt la grille de l'indice la taille du tableau - 1 à 1 pour chaque ligne
			if (lign_can_move(g, i, GRID_SIDE - 1, 1, SENS_NEGATIF))
				return true;
		}
		break;
	case UP:
		for (int i = 0; i < GRID_SIDE; i++) {
			// ici on parcourt la grille de l'indice 0 à la taille du tableau pour chaque colonne
			if (column_can_move(g, i, 0, GRID_SIDE, SENS_POSITIF))
				return true;
		}
		break;
	case DOWN:
		for (int i = 0; i < GRID_SIDE; i++) {
			// ici on parcourt la grille de l'indice la taille du tableau - 1 à 1 pour chaque colonne
			if (column_can_move(g, i, GRID_SIDE - 1, 1, SENS_NEGATIF))
				return true;
		}
		break;
	default:
		return false;
	}

	return false;
}

/**
 * \Vérifie le statut du jeu, s'il n'y a plus de mouvement possible, le jeu est perdu
 * \paramètre g, la grille
 * \retourne vrai s'il n'y a plus de mouvement possible, faux sinon
 */
bool game_over(grid g) {
	return !can_move(g, LEFT) && !can_move(g, RIGHT) && !can_move(g, UP)
			&& !can_move(g, DOWN);
}

/**
 * \Déplace toutes les tuiles de la grille dans la direction spécifiée par l'utilisateur
 * \param g the grid
 * \param d the chosen direction
 * \pre the movement d must be possible (i.e. can_move(g,d) == true).
 */
void do_move(grid g, dir d) {

	unsigned long int to_add = 0;

	if (!can_move(g, d)) {
		return;
	}

	// en fonction de la direction passée en paramètre, on fait un mouvement ligne à ligne ou colonne à colonne.
	if (d == LEFT || d == RIGHT) {
		for (int i = 0; i < GRID_SIDE; i++) {
			to_add += lign_do_move(g, i, d);
		}
	}

	if (d == UP || d == DOWN) {
		for (int j = 0; j < GRID_SIDE; j++) {
			to_add += column_do_move(g, j, d);
		}
	}

	// on ajoute au score les résultats de chaque ligne ou colonne.
	g->score += to_add;

}

/**
 * \Ajoute aléatoirement une tuile dans la grille à un espace libre dont la valeur sera 2 ou 4
 * \paramètre g, la grille
 * \La grille doit contenir au moins une tuile vide
 */
void add_tile(grid g) {
	int taille = (GRID_SIDE * GRID_SIDE) * 2; // taille maximale de notre tableau
	int nbFree = 0; // nombre de tuiles libres
	int* tab; // le tableau de coordonées
	int nombreAleatoire;

	tab = malloc(sizeof(int) * taille);
	// on parcourt la grille
	for (int i = 0; i < GRID_SIDE; i++) {
		for (int j = 0; j < GRID_SIDE; j++) {
			// si la tuile à la position (i,j) est vide on ajoute au tableau tab les valeurs de i et j
			if (g->tiles[i][j] == 0) {
				tab[nbFree * 2] = i;
				tab[nbFree * 2 + 1] = j;
				nbFree += 1;
			}
		}
	}

	if (nbFree == 0) {
		return;
	}

	// on génère un nombre aléatoire pour obtenir les coordonées dans le tableau tab d'une tuile vide
	nombreAleatoire = rang_aleatoire(nbFree) * 2;
	// on change la valeur de la tuile obtenue (9/10 chance d'avoir 1 et 1/10 chance d'avoir 2)
	g->tiles[tab[nombreAleatoire]][tab[nombreAleatoire + 1]] =
			valeur_aleatoire();
	free(tab);
}

/**
 * \Joue une direction dans la grille
 * \paramètre g, la grille
 * \paramètre d, la direction
 * \le mouvement d doit être possible (c-à-d, can_move(g,d) == true)
 */
void play(grid g, dir d) {
	// on fait le mouvement sur la grille
	do_move(g, d);

	// on ajoute une tuile à une position aléatoire
	add_tile(g);
}

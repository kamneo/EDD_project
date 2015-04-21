#ifndef _SDL_H_
#define _SDL_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
/*
	Fichier sdl.h
	contient les fonctiosn et les constantes nécessaires à 2048_sdl.c .
*/



	/*Prototype des fonction*/

/* 
	Fonction qui initialise le tableau des couleurs disponible
	la dernière case du tableau sera toujours la couleur de l'écran, la première sera la couleur des tuiles vides,
	la seconde des tuiles à 2, la troisième des tuiles à 4 etc...
*/
void initTabColor(SDL_Surface *ecran);


/*
	fonction qui fait la puissance de 2 d'une tuile
*/
unsigned long int pow_of_2(tile t);


/*
	fonction qui affiche une grille
	ses paramètres sont: une grille, une police de caractères, la fenêtre principale, une position pour le score
*/
void display(grid g, TTF_Font *police,SDL_Surface *ecran);


void endGame(SDL_Surface *ecran);


#define NB_COLOR 13		// nombre de couleurs disponibles
#define TILE_SIZE 130	// taille en pixels d'un côté d'une tuile
#define EDGE 10			// nombre de pixels entre les tuiles
#define MAX_CARACTERE 50// taille de la chaine de caractères des messages à afficher




#endif
#ifndef _SDL_H_
#define _SDL_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
/*
	Fichier sdl.h
	contient les fonction et les constante necessaire a 2048_sdl.c .
*/


	/*Prototype des fonction*/

void initTabColor(SDL_Surface *ecran);
/* 
	Fonction qui initialise le tableau des couleur disponible
	la derniere case du tableau sera toujours la couleur de l'écrans la premiere les tile vide
	la seconde les tile a 2 la troisieme les tile a 4 etc...
*/

unsigned long int pow_of_2(tile t);
/*
	fonction qui retourne le score de la tile
*/

void display(grid g, TTF_Font *police,SDL_Surface *ecran,SDL_Rect posScore);
/*
	fonction qui affiche une grid
	ces paramétre sont: une grid , une police de caractere, la fenetre principale , une position pour le score)
*/


#define NB_COLOR 14		// nombre de couleur disponible
#define TILE_SIZE 120	// taille en pixel d'un cote d'une tile
#define EDGE 10			// nombre de pixels entre les tiles
#define MAX_CARACTERE 20// taille de la chaine de caractere des message a afficher




#endif
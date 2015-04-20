#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <grid.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


	/*Prototype des fonction*/

void initTabColor(SDL_Surface *ecran);
unsigned long int pow_of_2(tile t);
void display(grid g, TTF_Font *police,SDL_Surface *ecran,SDL_Rect posScore);


	/*Declaration des variable*/

#define nbColor 14					// nombre de couleur disponible

static int tile_size = 120;			// taille en pixel d'un cote d'une tile
static int bordur=10;				// nombre de pixels entre les tiles
static Uint32 ColorsTab[nbColor];	// tableau de couleur 
static int longueur;				// longueur de la fenetre
static int largeur;					// largeur de la fenetre
static SDL_Color couleurNoire = {0, 0, 0};			// couleur de police
static SDL_Color couleurBlanche = {255, 255, 255};	// couleur de police
static int police_size = 35; 						// taille de la police de caractere

/* Main*/

int main(int argc, char *argv[])
{
	srand(time(NULL));			// on initialise srand

	bool game=true;				// variable pour la boucle principale de la sdl
	bool tour_suivant; 			// valeur boolean est a vrai quand on veut continuer la partie
	dir direction;				// contient la direction a jouer pour chaque tour
	grid g;

	largeur = (tile_size*GRID_SIDE)+(bordur*(GRID_SIDE+1));			// on initialise la taille de la fenetre avec
	longueur = (tile_size*(GRID_SIDE+1))+(bordur*(GRID_SIDE+1));	// la taille des tile et la taille des bordure
																	// on se prevoit une marge en dessous pour le score

	SDL_Rect posScore;						// initialisation de la position du score
	posScore.y=longueur-(tile_size/2)-20;	// dans la fenetre. C'est pour cela qu'on avait prévu 
	posScore.x=largeur/2-45;				// la taille d'une tile de marge
											// les valeur soustrait a la fin sont arbitraire afin de bien trouver le milieu

	SDL_Surface *ecran = NULL;				// Le pointeur qui va pointer la fenetre principale
	SDL_Event event; 						// initialisation des évenements
  

    
	SDL_Init(SDL_INIT_VIDEO); 		// initialise sdl
	TTF_Init();						// initialisation de sdl_ttf (qui permet d'écrire sur l'écran)

	TTF_Font *police = NULL;						// initialisation de la police de caractere
	police= TTF_OpenFont("angelina.ttf" , police_size);	
  
	if(SDL_Init(SDL_INIT_VIDEO)==-1)		// on verifie si sdl c'est bien lancé
	{
		fprintf(stderr, "erreur initialisation SDL");
		exit(EXIT_FAILURE);
	}

	// On entre les caracteristique de l'écrans (longeur,largeur,couleur codé sur 32bit, option de fonctionnement)
	// (SDL_HWSURFACE stocke les valeur en ram et SDL_DOUBLEBUF évite le scintillement d'image)
    ecran = SDL_SetVideoMode(largeur,longueur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);	
	

	if(ecran == NULL)		// on verifie si l'écran c'est bien initialisé
	{
		fprintf(stderr, "Impossible de charger mode vidéo : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	initTabColor(ecran);		// on initialise le tableau de couleur pour quelle soit dans un format
								// utilisable par sdl.

	SDL_WM_SetCaption("2048 (SDL)", NULL); //titre fenetre

  
	/* Debut de la boucle des évenement de sdl*/

	while(game)
	{
		g=new_grid();
		add_tile(g);
		add_tile(g);
		tour_suivant=true;
		while(tour_suivant)
		{	
			display(g,police,ecran,posScore);
			SDL_WaitEvent(&event);
			switch(event.type)
			{

			case SDL_QUIT:
				game=0;
				tour_suivant=false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						game=0;
						tour_suivant=false;
						break;
					case SDLK_UP:
						direction=UP;
						break;
					case SDLK_DOWN:
						direction=DOWN;
						break;
					case SDLK_RIGHT:
						direction=RIGHT;
						break;
					case SDLK_LEFT:
						direction=LEFT;
						break;
					case SDLK_r:
						tour_suivant=false;
						break;
						default:
							continue;
				}
				break;
				default:
					continue;
			}
			if(!can_move(g, direction))
				{
				continue;
				}
			play(g,direction);
			if(game_over(g))
				tour_suivant=false;
		}
		delete_grid(g);
	}
	SDL_FreeSurface(ecran);
	TTF_Quit();
	SDL_Quit(); //quitte sdl

	return EXIT_SUCCESS;
}

void display(grid g, TTF_Font *police, SDL_Surface *ecran,SDL_Rect posScore)
{
	SDL_FillRect(ecran,NULL,ColorsTab[nbColor-1]);
	SDL_Rect posTile;
	SDL_Rect posValue_Tile;
	posValue_Tile.x=tile_size/2-5;
	posValue_Tile.y=tile_size/2-15;

	char s[20];
	int valTile;
	int score;


	for(int x=0;x<GRID_SIDE;x++)
	{
		for (int y=0;y<GRID_SIDE;y++)
		{
			SDL_Surface *tile_Sdl = NULL;
			SDL_Surface *texte=NULL;
			tile_Sdl=SDL_CreateRGBSurface(SDL_HWSURFACE,tile_size,tile_size,32,0,0,0,0);
			valTile=get_tile(g,x,y);
			SDL_FillRect(tile_Sdl,NULL,ColorsTab[valTile%14]);
			sprintf(s,"%ld",pow_of_2(valTile));
			if(valTile)
				texte= TTF_RenderText_Blended(police, s, couleurNoire);
			if(valTile%nbColor-2==0 && valTile!=0)
				texte= TTF_RenderText_Blended(police, s, couleurBlanche);
			posTile.y=(bordur*(x+1))+tile_size*x;
			posTile.x=(bordur*(y+1))+tile_size*y;

			SDL_BlitSurface(texte , NULL , tile_Sdl, &posValue_Tile);
			SDL_BlitSurface(tile_Sdl,NULL,ecran, &posTile);
			SDL_FreeSurface(texte);
			SDL_FreeSurface(tile_Sdl);
		}
	}
	score=grid_score(g);
	sprintf(s,"score : %d",score);
	SDL_Surface *sdlScore=NULL;
	sdlScore= TTF_RenderText_Blended(police, s, couleurNoire);
	SDL_BlitSurface(sdlScore , NULL , ecran, &posScore);
	SDL_FreeSurface(sdlScore);

	SDL_Flip(ecran); //mise-à-jour de ecran
}


unsigned long int pow_of_2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

	/* Initiaisation du tableau place des couleur dans le format des couleur sdl et le format choisit pour l'écrans */
void initTabColor(SDL_Surface *ecran)
{
	ColorsTab[0]=SDL_MapRGB(ecran->format, 206, 206, 206);
	ColorsTab[1]=SDL_MapRGB(ecran->format, 254, 254, 226);
	ColorsTab[2]=SDL_MapRGB(ecran->format, 253, 241, 184);
	ColorsTab[3]=SDL_MapRGB(ecran->format, 255, 203, 96);
	ColorsTab[4]=SDL_MapRGB(ecran->format, 254, 163, 71);
	ColorsTab[5]=SDL_MapRGB(ecran->format, 231, 62, 1);
	ColorsTab[6]=SDL_MapRGB(ecran->format, 255, 255, 107);
	ColorsTab[7]=SDL_MapRGB(ecran->format, 255, 215, 0);
	ColorsTab[8]=SDL_MapRGB(ecran->format, 255, 255, 0);
	ColorsTab[9]=SDL_MapRGB(ecran->format, 255, 73, 1);
	ColorsTab[10]=SDL_MapRGB(ecran->format, 247, 35, 12);
	ColorsTab[11]=SDL_MapRGB(ecran->format, 255, 0, 0);
	ColorsTab[12]=SDL_MapRGB(ecran->format, 0,0,0);
	ColorsTab[13]=SDL_MapRGB(ecran->format, 186, 186, 186);
}

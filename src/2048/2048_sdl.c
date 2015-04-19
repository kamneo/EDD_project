#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <grid.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


//#define NOUVELLE_PARTIE 1

unsigned long int pow_of_2(tile t);
void display(grid g, TTF_Font *police,SDL_Surface *ecran,SDL_Rect *posScore);
int tile_size = 120; //taille en pixel d'un cote d'une tile
int bordur=10; //nombre de pixels entre les tiles

int longueur;
int largeur;


int main(int argc, char *argv[]){
	srand(time(NULL));

	bool tour_suivant;		// valeur boolean est a vrai quand on veut continui la partie
	dir direction;			// contient la direction décrite dans grid.h
	grid g;
	int game=1;				// variable pour la boucle principale de la sdl
	largeur = (tile_size*GRID_SIDE)+(bordur*(GRID_SIDE+1));
	longueur = (tile_size*(GRID_SIDE+1))+(bordur*(GRID_SIDE+1));

	SDL_Surface *ecran = NULL;
	SDL_Event event; //initialisation de l'évenement

	SDL_Rect posScore;
	posScore.x=longueur-tile_size;
	posScore.y=largeur/2;
  

    
	SDL_Init(SDL_INIT_VIDEO); //initialise sdl
	TTF_Init();

	TTF_Font *police = NULL;
	police= TTF_OpenFont("angelina.ttf" , 30);
  
	if(SDL_Init(SDL_INIT_VIDEO)==-1){
		fprintf(stderr, "erreur initialisation SDL");
		exit(EXIT_FAILURE);
	}

    ecran = SDL_SetVideoMode(largeur,longueur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	

	if(ecran == NULL){
		fprintf(stderr, "Impossible de charger mode vidéo : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption("2048 (SDL)", NULL); //titre fenetre
	SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 255, 255, 255)); //couleur unique de ecran
  

	while(game)
	{
		g=new_grid();
		add_tile(g);
		add_tile(g);
		tour_suivant=true;
		while(tour_suivant)
		{	
			display(g,police,ecran,&posScore);
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

void display(grid g, TTF_Font *police, SDL_Surface *ecran, SDL_Rect *posScore){


	SDL_Rect posTile;
	SDL_Rect posValue_Tile;
	posValue_Tile.x=tile_size/2;
	posValue_Tile.y=tile_size/2;
	char s[20];
	int valTile;
	int score;
	SDL_Color couleurNoire = {0, 0, 0};


	for(int x=0;x<GRID_SIDE;x++){
		for (int y=0;y<GRID_SIDE;y++){
			SDL_Surface *tile_Sdl = NULL;
			SDL_Surface *texte=NULL;
			tile_Sdl=SDL_CreateRGBSurface(SDL_HWSURFACE,tile_size,tile_size,32,0,0,0,0);
			SDL_FillRect(tile_Sdl,NULL,SDL_MapRGB(ecran->format, 50, 120, 200));
			valTile=get_tile(g,x,y);
			sprintf(s,"%ld",pow_of_2(valTile));
			texte= TTF_RenderText_Blended(police, s, couleurNoire);
			posTile.y=(bordur*(x+1))+tile_size*x;
			posTile.x=(bordur*(y+1))+tile_size*y;
			SDL_BlitSurface(texte , NULL , tile_Sdl, &posValue_Tile);
			SDL_BlitSurface(tile_Sdl,NULL,ecran, &posTile);
			SDL_FreeSurface(texte);
			SDL_FreeSurface(tile_Sdl);
		}
	}

	SDL_Surface *sdl_score =NULL;
	score=grid_score(g);
	sprintf(s,"%d",score);
	sdl_score= TTF_RenderText_Blended(police, s, couleurNoire);
	SDL_BlitSurface(sdl_score , NULL , ecran, posScore);

	SDL_Flip(ecran); //mise-à-jour de ecran
}


unsigned long int pow_of_2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

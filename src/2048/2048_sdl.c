#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <grid.h>
#include <SDL/SDL.h>

#define NOUVELLE_PARTIE 1

void pause();
unsigned long int pow_of_2(tile t);

int main(int argc, char *argv[]){
  
  SDL_Surface *ecran = NULL;
  SDL_Surface *grille = NULL; //autre surface
  SDL_Rect posGrille; //position de la nouvelle surface par rapport a ecran

  posGrille.x = 400/2 -80/2;
  posGrille.y = 400/2 -100/2;
    
  SDL_Init(SDL_INIT_VIDEO); //initialise sdl
  
  if(SDL_Init(SDL_INIT_VIDEO)==-1){
    fprintf(stderr, "erreur initialisation SDL");
    exit(EXIT_FAILURE);
  }

    
  ecran = SDL_SetVideoMode(400, 400, 32, SDL_HWSURFACE);
  grille = SDL_CreateRGBSurface(SDL_HWSURFACE,80,100,32,0,0,0,0);

  if(ecran == NULL){
    fprintf(stderr, "Impossible de charger mode vidéo : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  
  SDL_WM_SetCaption("2048 (SDL)", NULL); //titre fenetre
  SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 255, 255, 255)); //couleur unique de ecran
  SDL_FillRect(grille,NULL,SDL_MapRGB(ecran->format, 0, 255, 255));
  SDL_BlitSurface(grille,NULL,ecran, &posGrille); // (surface à coller,partie de la surface,surface sur laquelle on colle,position sur ecran)
  
  SDL_Flip(ecran); //mise-à-jour de ecran

  pause();

  SDL_FreeSurface(grille);
  SDL_Quit(); //quitte sdl

  return EXIT_SUCCESS;
  
}

void pause(){
    int continuer = 1;
    SDL_Event event;
 
    while (continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
        }
    }
} 

unsigned long int pow_of_2(tile t)
{
	if (t == 0)	
		return t;
	return pow(2, t);
}

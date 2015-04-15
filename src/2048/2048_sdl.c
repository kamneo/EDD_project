#include <stdlib.h>
#include <stdio.h>
#include <grid.h>
#include <SDL/SDL.h>

void pause();

int main(int argc, char *argv[]){
  
  SDL_Surface *ecran = NULL;
  
  SDL_Init(SDL_INIT_VIDEO); //initialise sdl
  if(SDL_Init(SDL_INIT_VIDEO)==-1){
    fprintf(stderr, "erreur initialisation SDL");
    exit(EXIT_FAILURE);
  }

    
  ecran = SDL_SetVideoMode(400, 400, 32, SDL_HWSURFACE);

  if(ecran == NULL){
    fprintf(stderr, "Impossible de charger mode vidéo : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  
  SDL_WM_SetCaption("2048 (SDL)", NULL); //titre fenetre
  SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 255, 255, 255));

  SDL_Flip(ecran);

  pause();

  
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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <grid.h>
#include <time.h>
#include <sdl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


	/*Declaration des variable*/


static char s[MAX_CARACTERE];		// creer la chaine de caractere qui aceuillera les messages a afficher
static Uint32 ColorsTab[NB_COLOR];	// tableau de couleur 
static int longueur;				// longueur de la fenetre
static int largeur;					// largeur de la fenetre
static SDL_Color couleurNoire = {0, 0, 0};			// couleur de police
static int police_size = 40; 						// taille de la police de caractere

/* Main*/

int main(int argc, char *argv[])
{
	srand(time(NULL));			// on initialise srand

	bool game=true;				// variable pour la boucle principale de la sdl
	bool tour_suivant; 			// valeur boolean est a vrai quand on veut continuer la partie
	dir direction;				// contient la direction a jouer pour chaque tour
	grid g;

	largeur = (TILE_SIZE*GRID_SIDE)+(EDGE*(GRID_SIDE+1));			// on initialise la taille de la fenetre avec
	longueur = (TILE_SIZE*(GRID_SIDE+1))+(EDGE*(GRID_SIDE+1));		// la taille des tile et la taille des EDGEe
																	// on se prevoit une marge en dessous pour le score

											// les valeur soustrait a la fin sont arbitraire afin de bien trouver le milieu

	SDL_Surface *ecran = NULL;				// Le pointeur qui va pointer la fenetre principale
	SDL_Event event; 						// initialisation des évenements


	SDL_Init(SDL_INIT_VIDEO); 				// initialise sdl
	TTF_Init();								// initialisation de sdl_ttf (qui permet d'écrire sur l'écran)

	TTF_Font *police = NULL;								// initialisation de la police de caractere
	police= TTF_OpenFont("angelina.ttf" , police_size);	
  
	if(SDL_Init(SDL_INIT_VIDEO)==-1)						// on verifie si sdl c'est bien lancé
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

	//SDL_WM_SetCaption("2048 (SDL)", NULL); //titre fenetre

  
	/* Debut de la boucle des évenement de sdl*/

	while(game)
	{
		g=new_grid();				//initialisation de la grid
		add_tile(g);
		add_tile(g);
		
		tour_suivant=true;
		while(tour_suivant)			//boucle de la partie
		{	
			display(g,police,ecran);
			SDL_WaitEvent(&event);
			switch(event.type)
			{

			case SDL_QUIT:			// permet la fermeture de la fenetre par clic sur la croix
				game=0;
				tour_suivant=false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)		// switch des event de pression des touches
				{
				case SDLK_ESCAPE:					// la touche echap ferme la fenetre
					game=0;
					tour_suivant=false;
					break;
				case SDLK_UP:						// la fleche directionnelle haut joue en haut
					direction=UP;
					break;
				case SDLK_DOWN:						// la fleche directionnelle bas joue en bas
					direction=DOWN;
					break;
				case SDLK_RIGHT:					// la fleche directionnelle droite joue a droite
					direction=RIGHT;
					break;
				case SDLK_LEFT:						// la fleche directionnelle gauche joue a gauche
					direction=LEFT;
					break;
				case SDLK_r:						// la touche r recommence une nouvelle partie
					tour_suivant=false;
					break;
					default:
						continue;
				}
				break;
				default:
					continue;
			}
			play(g,direction);						// on joue dans la direction delectionné

			/* Boucle du game over */

			if(game_over(g))
			{
				endGame(ecran);						// on affiche le game over
				while (tour_suivant)				// on rentre dans la boucle des evenement lié au game over
				{
					SDL_WaitEvent(&event);
					switch(event.type)
					{
					case SDL_QUIT:					// se sont globalement les mèmes evenements
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
						case SDLK_r:
							tour_suivant=false;
							break;
						default:
							continue;
						}
					break;
					}
				}// fin while game_over
			}//fin if game over
					
		
		}// fin while tour_suivant
		delete_grid(g);						// on detruit la grille entre les deux whiles
	}// fin while game

	TTF_CloseFont (police);					// free de la police de caractere
	SDL_FreeSurface(ecran);					// free de la surface ecran
	TTF_Quit();								// on ferme ttf
	SDL_Quit(); 							// on ferme sdl

	return EXIT_SUCCESS;
}


/* fonction affichant l'écrans de jeux */

void display(grid g, TTF_Font *police, SDL_Surface *ecran)
{
	SDL_FillRect(ecran,NULL,ColorsTab[NB_COLOR-1]);			//on reinitialise l'écrans pour ne pas réecrire par dessus	

	SDL_Rect posTile;										// Cette variable acceuillera les position ou l'on collera les tiles sur l'écrans
	SDL_Rect posTexte;										// Cette variable acceuillera les position ou l'on collera les textes sur l'écrans
	SDL_Surface *tile_Sdl = NULL;							// Surface correspondant au tile
	SDL_Surface *texte = NULL;								// Surface de texte

	int valTile;											// contiendra les valeurs des tiles


/*	Affichage des tiles */

	for(int x=0;x<GRID_SIDE;x++)							// Boucle de parcourt de la grid
	{
		for (int y=0;y<GRID_SIDE;y++)
		{

			tile_Sdl=SDL_CreateRGBSurface(SDL_HWSURFACE,TILE_SIZE,TILE_SIZE,32,0,0,0,0);	// on créer la surface en mode 32bit et de taille tile_size
			valTile=get_tile(g,x,y);														// on recup la valeur de la tile
			SDL_FillRect(tile_Sdl,NULL,ColorsTab[valTile%(NB_COLOR-2)]);					// on colorie la surface dans la couleur correspondant a sa valeur	
			sprintf(s,"%ld",pow_of_2(valTile));												// on transforme notre valeur de tile en chaine de caractere
			posTile.y=(EDGE*(x+1))+TILE_SIZE*x;												// on genere la position en fonction de EDGE(bordure) et tile_size
			posTile.x=(EDGE*(y+1))+TILE_SIZE*y;

			if(valTile!=0)
			{
				texte= TTF_RenderText_Blended(police, s, couleurNoire);						// on genere la surface a partir de la chaine de caractere
				posTexte.x=(TILE_SIZE/2)-(texte->w/2);										// on initialise la posTexte au milieu de la tile et qui se re decal tout seul
				posTexte.y=(TILE_SIZE/2)-(texte->h/2);
				SDL_BlitSurface(texte , NULL , tile_Sdl, &posTexte);						// on colle le texte sur la tile fraichement générer
				SDL_FreeSurface(texte);														// on libere la surface de texte
			}
			SDL_BlitSurface(tile_Sdl,NULL,ecran, &posTile);									// on colle la surface de la tuile a l'écran
			SDL_FreeSurface(tile_Sdl);
		}
	}//fin de boucle for

	/*Cette partie marche comme la précedente sauf que l'on va determiner les positions de maniere plus arbitraire a savoir
		le score : au millieu de la place qu'il nous reste sous les tiles
		le restart : en bas a gauche de la place restante
		le quit : en haut a gauche de la place restante 
	*/


	/* Affichage du score */

	sprintf(s,"score : %lu",grid_score(g));
	texte= TTF_RenderText_Blended(police, s, couleurNoire);
	posTexte.y=longueur-(TILE_SIZE/2)-(texte->h/2);	
	posTexte.x=largeur/2-(texte->w/2);				
	SDL_BlitSurface(texte , NULL , ecran, &posTexte);
	SDL_FreeSurface(texte);

	/* Affichage du restart */

	sprintf(s,"press r to restart");
	texte= TTF_RenderText_Blended(police, s, couleurNoire);
	posTexte.y=longueur-(TILE_SIZE/3);
	posTexte.x=EDGE;
	SDL_BlitSurface(texte , NULL , ecran, &posTexte);
	SDL_FreeSurface(texte);

	/* Affichage du quit */

	sprintf(s,"press ESC to quit");
	texte= TTF_RenderText_Blended(police, s, couleurNoire);
	posTexte.y=longueur-(TILE_SIZE);
	posTexte.x=EDGE;
	SDL_BlitSurface(texte , NULL , ecran, &posTexte);
	SDL_FreeSurface(texte);

	SDL_Flip(ecran); //mise-à-jour de ecran
}


	/* Fonction qui affiche un game over en plein millieu de l'écrans */

void endGame( SDL_Surface *ecran)
{
	TTF_Font *police = NULL;
	police= TTF_OpenFont("angelina.ttf" , police_size*3);	
	SDL_Rect posTexte;
	SDL_Surface *texte = NULL;
	sprintf(s,"GAME OVER");
	texte= TTF_RenderText_Blended(police, s, couleurNoire);
	posTexte.y=longueur/2-(texte->h/2);
	posTexte.x=largeur/2-(texte->w/2);
	SDL_BlitSurface(texte , NULL , ecran, &posTexte);

	TTF_CloseFont (police);
	SDL_FreeSurface(texte);

	SDL_Flip(ecran);
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
	ColorsTab[0]=SDL_MapRGB(ecran->format, 206, 206, 206);		//couleur des tile vide
	ColorsTab[1]=SDL_MapRGB(ecran->format, 254, 254, 226);		// couleur des tile a 2	
	ColorsTab[2]=SDL_MapRGB(ecran->format, 253, 241, 184);		// couleur des tile a 4
	ColorsTab[3]=SDL_MapRGB(ecran->format, 255, 203, 96);		//etc...
	ColorsTab[4]=SDL_MapRGB(ecran->format, 254, 163, 71);
	ColorsTab[5]=SDL_MapRGB(ecran->format, 231, 62, 1);
	ColorsTab[6]=SDL_MapRGB(ecran->format, 255, 255, 107);
	ColorsTab[7]=SDL_MapRGB(ecran->format, 255, 215, 0);
	ColorsTab[8]=SDL_MapRGB(ecran->format, 255, 255, 0);
	ColorsTab[9]=SDL_MapRGB(ecran->format, 255, 73, 1);
	ColorsTab[10]=SDL_MapRGB(ecran->format, 247, 35, 12);
	ColorsTab[11]=SDL_MapRGB(ecran->format, 255, 0, 0);
	ColorsTab[12]=SDL_MapRGB(ecran->format, 186, 186, 186);		// couleur de l'écran
}

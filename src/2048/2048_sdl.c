#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <grid.h>
#include <time.h>
#include <sdl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


	/*Déclaration des variables*/


static char s[MAX_CARACTERE];		// créé la chaine de caractères qui accueillera les messages à afficher
static Uint32 ColorsTab[NB_COLOR];	// tableau de couleurs 
static int longueur;				// longueur de la fenêtre
static int largeur;					// largeur de la fenêtre
static SDL_Color couleurNoire = {0, 0, 0};			// couleur de police
static int police_size = 40; 						// taille de la police de caractères

/* Main*/

int main(int argc, char *argv[])
{
	srand(time(NULL));			// on initialise srand

	bool game=true;				// variable pour la boucle principale de la sdl
	bool tour_suivant; 			// valeur boolean est à vrai quand on veut continuer la partie
	dir direction;				// contient la direction à jouer pour chaque tour
	grid g;

	largeur = (TILE_SIZE*GRID_SIDE)+(EDGE*(GRID_SIDE+1));			// on initialise la taille de la fenêtre avec
	longueur = (TILE_SIZE*(GRID_SIDE+1))+(EDGE*(GRID_SIDE+1));		// la taille des tuiles et la taille des EDGE(bordure)
																	// on se prevoit une marge en dessous pour le score

											// les valeurs soustraites à la fin sont arbitraires afin de bien trouver le milieu

	SDL_Surface *ecran = NULL;				// Le pointeur qui va pointer la fenêtre principale
	SDL_Event event; 						// initialisation des évenements


	SDL_Init(SDL_INIT_VIDEO); 				// initialise sdl
	TTF_Init();								// initialisation de sdl_ttf (qui permet d'écrire sur l'écran)

	TTF_Font *police = NULL;								// initialisation de la police de caractères
	police= TTF_OpenFont("angelina.ttf" , police_size);	
  
	if(SDL_Init(SDL_INIT_VIDEO)==-1)						// on vérifie si sdl s'est bien lancé
	{
		fprintf(stderr, "erreur initialisation SDL");
		exit(EXIT_FAILURE);
	}

	// On entre les caractéristiques de l'écran (longueur,largeur,couleur codée sur 32bit, options de fonctionnement)
	// (SDL_HWSURFACE stocke les valeurs en ram et SDL_DOUBLEBUF évite le scintillement d'image)
    ecran = SDL_SetVideoMode(largeur,longueur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);	
	

	if(ecran == NULL)		// on vérifie si l'écran s'est bien initialisé
	{
		fprintf(stderr, "Impossible de charger mode vidéo : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	initTabColor(ecran);		// on initialise le tableau de couleurs pour qu'elles soient dans un format
								// utilisable par sdl

	//SDL_WM_SetCaption("2048 (SDL)", NULL); //titre fenêtre

  
	/* Début de la boucle des évenements de sdl*/
	while(game)
	{
		g=new_grid();				//initialisation de la grille
		add_tile(g);
		add_tile(g);
		
		tour_suivant=true;
		while(tour_suivant)			//boucle de la partie
		{	
			display(g,police,ecran);
			SDL_WaitEvent(&event);
			switch(event.type)
			{

			case SDL_QUIT:			// permet la fermeture de la fenêtre par clic sur la croix
				game=0;
				tour_suivant=false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)		// switch des events de pression des touches
				{
				case SDLK_ESCAPE:					// la touche echap ferme la fenêtre
					game=0;
					tour_suivant=false;
					break;
				case SDLK_UP:						// la flèche directionnelle haut joue en haut
					direction=UP;
					break;
				case SDLK_DOWN:						// la flèche directionnelle bas joue en bas
					direction=DOWN;
					break;
				case SDLK_RIGHT:					// la flèche directionnelle droite joue à droite
					direction=RIGHT;
					break;
				case SDLK_LEFT:						// la flèche directionnelle gauche joue à gauche
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
			play(g,direction);						// on joue dans la direction sélectionnée

			/* Boucle du game over */

			if(game_over(g))
			{
				endGame(ecran);						// on affiche le game over
				while (tour_suivant)				// on entre dans la boucle des évenements liés au game over
				{
					SDL_WaitEvent(&event);
					switch(event.type)
					{
					case SDL_QUIT:					// ce sont globalement les mêmes évenements
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
		delete_grid(g);						// on détruit la grille entre les deux whiles
	}// fin while game 

	TTF_CloseFont (police);					// free de la police de caractères
	SDL_FreeSurface(ecran);					// free de la surface ecran
	TTF_Quit();								// on ferme ttf
	SDL_Quit(); 							// on ferme sdl

	return EXIT_SUCCESS;
}


/* fonction affichant l'écran de jeu */
void display(grid g, TTF_Font *police, SDL_Surface *ecran)
{
	SDL_FillRect(ecran,NULL,ColorsTab[NB_COLOR-1]);			//on réinitialise l'écran pour ne pas reécrire par dessus	

	SDL_Rect posTile;										// Cette variable accueillera les positions où on collera les tuiles sur l'écran
	SDL_Rect posTexte;										// Cette variable accueillera les positions où on collera les textes sur l'écran
	SDL_Surface *tile_Sdl = NULL;							// Surface correspondant aux tuiles
	SDL_Surface *texte = NULL;								// Surface de texte

	int valTile;											// contiendra les valeurs des tuiles


/*	Affichage des tiles */
	for(int x=0;x<GRID_SIDE;x++)							// Boucle de parcourt de la grille
	{
		for (int y=0;y<GRID_SIDE;y++)
		{

			tile_Sdl=SDL_CreateRGBSurface(SDL_HWSURFACE,TILE_SIZE,TILE_SIZE,32,0,0,0,0);	// on créé la surface en mode 32bit et de taille tile_size
			valTile=get_tile(g,x,y);														// on recupère la valeur de la tuile
			SDL_FillRect(tile_Sdl,NULL,ColorsTab[valTile%(NB_COLOR-2)]);					// on colorie la surface de la couleur correspondante à sa valeur	
			sprintf(s,"%ld",pow_of_2(valTile));												// on transforme notre valeur de tuile en chaine de caractères
			posTile.y=(EDGE*(x+1))+TILE_SIZE*x;												// on génère la position en fonction de EDGE(bordure) et tile_size
			posTile.x=(EDGE*(y+1))+TILE_SIZE*y;

			if(valTile!=0)
			{
				texte= TTF_RenderText_Blended(police, s, couleurNoire);						// on génère la surface à partir de la chaine de caractères
				posTexte.x=(TILE_SIZE/2)-(texte->w/2);										// on initialise la posTexte au milieu de la tuile et qui se redecale toute seule
				posTexte.y=(TILE_SIZE/2)-(texte->h/2);
				SDL_BlitSurface(texte , NULL , tile_Sdl, &posTexte);						// on colle le texte sur la tuile fraichement générée
				SDL_FreeSurface(texte);														// on libère la surface de texte
			}
			SDL_BlitSurface(tile_Sdl,NULL,ecran, &posTile);									// on colle la surface de la tuile à l'écran
			SDL_FreeSurface(tile_Sdl);
		}
	}//fin de boucle for

	/*Cette partie marche comme la précédente sauf que l'on va déterminer les positions de manière plus arbitraire, à savoir:
		le score : au milieu de la place qu'il nous reste sous les tuiles
		le restart : en bas à gauche de la place restante
		le quit : en haut à gauche de la place restante 
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

	SDL_Flip(ecran); //mise-à-jour de écran
}


/* Fonction qui affiche un game over en plein milieu de l'écran */
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


/* Initialisation du tableau, place des couleurs dans le format des couleurs sdl et le format choisit pour l'écran */
void initTabColor(SDL_Surface *ecran)
{
	ColorsTab[0]=SDL_MapRGB(ecran->format, 206, 206, 206);		//couleur des tuiles vides
	ColorsTab[1]=SDL_MapRGB(ecran->format, 254, 254, 226);		// couleur des tuiles à 2	
	ColorsTab[2]=SDL_MapRGB(ecran->format, 253, 241, 184);		// couleur des tuiles à 4
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

#include <stdlib.h>
#include <stdio.h>
#include <grid.h>
#include <affichage.h>

#define NOUVELLE_PARTIE 1
int main(void){
	char c;
	bool tour_suivant;

	while(NOUVELLE_PARTIE){

		grid g=new_grid();
		add_tile(g);
		add_tile(g);
		display_grid(g);
		tour_suivant=true;

		while(tour_suivant){
			c=getchar();

			switch(c){
				case 'z':
					play(g, UP);
					break;
				case 'q':
					play(g, LEFT);
					break;
				case 's':
					play(g, DOWN);
					break;
				case 'd':
					play(g, RIGHT);
					break;
				default:
					continue;
					break;
			}
			
			display_grid(g);

			if (game_over(g)){
				printf("voulez vous rejouer : y , n\n");
				c=getchar();
				if (c=='y')
					tour_suivant=false;
				
				if (c=='n')
					return EXIT_SUCCESS;
			}		
				
		}
	}

}

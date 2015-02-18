#include <stdlib.h>
#include <stdio.h>
#include <grid.h>
#include <affichage.h>

int main(void){
	char c;
	bool boucle;
	while(1){
		grid g=new_grid();
		display_grid(g);
		boucle=true;
		while(boucle){
			//if(scanf("direction ? %c",&c)!=1)
			c=getchar();

			switch(c){
				case 'z':
					play(g,UP);
					display_grid(g);
					break;
				case 'q':
					play(g,LEFT);
					display_grid(g);
					break;
				case 's':
					play(g,DOWN);
					display_grid(g);
					break;
				case 'd':
					play(g,RIGHT);
					display_grid(g);
					break;
				default:
					break;

			}
			if (game_over(g)){
				printf("voulez vous rejouer : y , n ");
				c=getchar();
				if (c=='y')
					boucle=false;
				
				if (c=='n')
					return EXIT_SUCCESS;
			}		
				
		}
	}

}
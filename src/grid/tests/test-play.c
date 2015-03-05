

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <grid.h>




int main (int argc, char** argv){
	srand(time(NULL));
	unsigned long int score[10000];
	int nbGame=0;
	unsigned long int s=0;
	while(nbGame<10000){
		grid g;
		g=new_grid();
		add_tile(g);
		add_tile(g);
		while (!game_over(g)){

			if (can_move(g,LEFT)){
				play(g,LEFT);
			}
			else if (can_move(g,DOWN)){
				play(g,DOWN);
			}
			else if (can_move(g,RIGHT)){
				play(g,RIGHT);
			}
			else if (can_move(g,UP)){
				play(g,UP);
			}
			add_tile(g);
		}
		score[nbGame]=grid_score(g);
		nbGame+=1;
		delete_grid(g);

	}
	int p=0;
	s=score[0];
	for (int i=1;i<nbGame;i++){
		if (s<score[i]){
			s=score[i];
			p=i;
		}
	}
	printf("partie %d score: %lu\n",p,s);
	return EXIT_SUCCESS;
}

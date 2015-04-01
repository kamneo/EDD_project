#include "strategy.h"
#include "stdlib.h"
#include <assert.h>

void free_memless_strat (strategy strat)
{
  free (strat);
}




dir nextDirectionTrivial1(strategy s,grid g){//variante de la strategy du point
	int* nbTour=s->mem; //nombre de tour jouer
	if ((*nbTour)%2==0){ 

		if (can_move(g,LEFT)){
			return LEFT;
		}
		else if (can_move(g,DOWN)){
			return DOWN;
		}
		else if (can_move(g,RIGHT)){
			return RIGHT;
		}
		else {
			return UP;
		}
	}


	else{
		if (can_move(g,DOWN)){
			return DOWN;
		}
		else if (can_move(g,LEFT)){
			return LEFT;
		}
		else if (can_move(g,RIGHT)){
			return RIGHT;
		}
		else {
			return UP;
		}
	}

	(*nbTour)++;
}


dir nextDirectionTrivial2(strategy s,grid g){ // strategy simple du coin

	if (can_move(g,LEFT)){
		return LEFT;
	}
	else if (can_move(g,DOWN)){
		return DOWN;
	}
	else if (can_move(g,RIGHT)){
		return RIGHT;
	}
	else {
		return UP;
	}
}

/*int main(void){
	strategy strat = malloc(sizeof(strategy));
	strat-> name = "Coins";
	strat-> play_move = nextDirection;
	strat->mem = NULL;
	strat->void free_strategy=free_memless_strat;
}*/
#include "strategy.h"
#include "stdlib.h"

void free_memless_strat (strategy strat)
{
  free (strat);
}




dir nextDirection(strategy s,grid g){

	if (can_move(g,LEFT)){
		return LEFT;
	}
	else if (can_move(g,DOWN)){
		return DOWN;
	}
	else if (can_move(g,UP)){
		return UP;
	}
	else {
		return RIGHT;
	}
}

/*int main(void){
	strategy strat = malloc(sizeof(strategy));
	strat-> name = "Coins";
	strat-> play_move = nextDirection;
	strat->mem = NULL;
	strat->void free_strategy=free_memless_strat;
}*/
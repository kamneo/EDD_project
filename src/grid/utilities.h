#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "grid.h"

extern void add_score(grid g, unsigned long int x);

extern unsigned long int puissanceDe2(tile t);

extern bool lign_can_move(grid g, int i, dir d);

extern bool colon_can_move(grid g, int j, dir d);

extern void add_ligne(grid g, int i,dir d);

extern void add_colon(grid g, int j,dir d);

extern void concat_ligne(grid g, int i,dir d);

extern void concat_colon(grid g, int j ,dir d);


extern void lign_do_move(grid g, int i, dir d);

extern void colon_do_move(grid g, int i, dir d);

#endif

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "grid.h"

extern bool lign_can_move(grid g, int i, int debut, int fin, int facteur);

extern bool colon_can_move(grid g, int j, int debut, int fin, int facteur);

extern void lign_do_move(grid g, int i, dir d);

extern void colon_do_move(grid g, int i, dir d);

#endif

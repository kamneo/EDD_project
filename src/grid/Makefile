CC= gcc

CFLAGS= -g -Wall -std=c99
LDFLAGS= -lm

test_grid : test_grid.o grid.o utilities.o affichage.o
	$(CC) test_grid.o grid.o utilities.o affichage.o $(LDFLAGS) -o $@

utilities.o: utilities.c utilities.h
affichage.o: affichage.c affichage.h
grid.o: grid.c grid.h affichage.h utilities.h
test_grid.o: test_grid.c grid.h affichage.h utilities.h

dep : 
	${CC} -MM *.c

clean :
	rm -f *.o test_grid

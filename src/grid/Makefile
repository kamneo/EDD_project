CC= gcc

CFLAGS= -g -Wall -std=c99
LDFLAGS= -lm

test_grid : test_grid.o grid.o
	$(CC) test_grid.o grid.o $(LDFLAGS) -o $@

grid.o: grid.c grid.h
test_grid.o: test_grid.c grid.h

dep : 
	${CC} -MM *.c

clean :
	rm -f *.o test_grid

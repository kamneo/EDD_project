CC= gcc

INCLUDEDIR = ../../include
LIBDIR = ../../lib
CFLAGS= -g -Wall -std=c99
CPPFLAGS= -I $(INCLUDEDIR)
LDFLAGS= -lm  -L $(LIBDIR) -lgrid

2048 : 2048.o
	$(CC) test_grid.o $(LDFLAGS) -o $@

2048.o: 2048.c grid.h affichage.h

install:
	mv 2048 ../../2048_executable

dep : 
	$(CC) -MM *.c

clean :
	rm -f *.o 2048

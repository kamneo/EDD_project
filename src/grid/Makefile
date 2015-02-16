CC= gcc

CFLAGS= -g -Wall -std=c99
LDFLAGS= -lm
INCLUDEDIR = ../../include
LIBDIR = ../../lib

test_grid : test_grid.o grid.o utilities.o affichage.o
	$(CC) test_grid.o grid.o utilities.o affichage.o $(LDFLAGS) -o $@

utilities.o: utilities.c utilities.h
affichage.o: affichage.c affichage.h
grid.o: grid.c grid.h affichage.h utilities.h
test_grid.o: test_grid.c grid.h affichage.h utilities.h

install: libgrid.a
	cp affichage.h grid.h $(INCLUDEDIR)
	cp libgrid.a $(LIBDIR)
	rm -f libgrid.a
	rm *.o test_grid

libgrid.a:
	ar -cr libgrid.a grid.o affichage.o utilities.o

dep : 
	${CC} -MM *.c

clean :
	rm -f *.o test_grid
	rm -f $(INCLUDEDIR)/affichage.h $(INCLUDEDIR)/grid.h $(LIBDIR)/libgrid.a

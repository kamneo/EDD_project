CC= gcc

INCLUDEDIR = ../../include
LIBDIR = ../../lib
CFLAGS= -g -Wall -std=c99
CPPFLAGS= -I $(INCLUDEDIR)
LDFLAGS= -L $(LIBDIR) -lgrid -lm

2048 : 2048.o
	$(CC) 2048.o $(LDFLAGS) -o $@

2048.o: 2048.c

install:
	mv 2048 ../../2048_executable

dep : 
	$(CC) -MM *.c

clean :
	rm -f *.o ../../2048_executable

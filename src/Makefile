CC = gcc
CFLAGS = -g -Wall
CPPFLAGS = 
SUBDIR = grid


install:  libgrid.a objects
	for i in ${SUBDIR} ; do\
		cp $$i/$$i.h ../../include; \
	done
	cp libgrid.a ../../lib
	rm -f libgrid.a

libgrid.a: 
	for i in ${SUBDIR} ; do\
		${MAKE} -C $$i; \
	done

objects:
	for i in ${SUBDIR} ; do\
		ar -r libgrid.a $$i/$$i.o;\
	done
	

.PHONY: clean
clean:
	for i in ${SUBDIR} ; do \
		${MAKE} clean -C $$i; \
	done


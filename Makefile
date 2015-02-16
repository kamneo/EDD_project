CC = gcc
CFLAGS = -g -Wall
CPPFLAGS = 
SUBDIR = grid


install: 
	for i in ${SUBDIR} ; do\
		${MAKE} -C $$i; \
	done

.PHONY: clean
clean:
	for i in ${SUBDIR} ; do \
		${MAKE} clean -C $$i; \
	done



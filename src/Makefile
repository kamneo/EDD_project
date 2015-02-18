CC = gcc
CFLAGS = -g -Wall
CPPFLAGS = 
SUBDIR = grid 2048

install: 
	for i in ${SUBDIR} ; do\
		${MAKE} -C $$i; \
		${MAKE} install -C $$i; \
	done

.PHONY: clean
clean:
	for i in ${SUBDIR} ; do \
		${MAKE} clean -C $$i; \
	done


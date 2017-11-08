CC       = gcc
CFLAGS   = -Wall -Werror -ansi -pedantic
CFLAGS  += -g
CFLAGS  += -D_XOPEN_SOURCE=500

malloc : biblio_alloc.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean realclean

clean: 
	rm -rf *~ *.o

realclean : clean
	rm -rf *~ *.o malloc

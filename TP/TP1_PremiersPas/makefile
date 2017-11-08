CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic
CFLAGS += -g

all: preprocesseur

preprocesseur: preprocesseur.c
	$(CC) $(CFLAGS) -o preprocesseur preprocesseur.c

clean:
	rm -f preprocesseur.o *~

realclean: clean
	rm -f preprocesseur

CC=gcc
CFLAGS=-g -Wall -Wmissing-prototypes
LDFLAGS=-g
objects := $(patsubst %.c,%.o,$(wildcard *.c))
all: main
clean:
	-rm $(objects)
	-rm main
main: $(objects)
# Les 3 lignes produites par gcc -MM *.c
chaine.o: chaine.c chaine.h liste_char.h
liste_char.o: liste_char.c liste_char.h
main.o: main.c chaine.h liste_char.h


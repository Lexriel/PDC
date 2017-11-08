CC=gcc
CFLAGS=-g -Wall -Wmissing-prototypes
LDFLAGS=-g
objects := $(patsubst %.c,%.o,$(wildcard *.c))
all: main
clean:
	-rm $(objects)
	-rm main
main: $(objects)
chaine.o: chaine.c chaine.h
main.o: main.c chaine.h
# Les 2 lignes produites par gcc -MM *.c
chaine.o: chaine.c chaine.h
main.o: main.c chaine.h


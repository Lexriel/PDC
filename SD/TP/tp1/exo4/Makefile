CC=gcc
CFLAGS=-g -Wall -Wmissing-prototypes
LDFLAGS=-g
objects := $(patsubst %.c,%.o,$(wildcard *.c))
all: main
clean:
	-rm $(objects)
	-rm main
main: $(objects)
caractere.o: caractere.c caractere.h
chaine.o: chaine.c chaine.h liste_caractere.h caractere.h
liste_caractere.o: liste_caractere.c liste_caractere.h caractere.h
main.o: main.c chaine.h liste_caractere.h caractere.h

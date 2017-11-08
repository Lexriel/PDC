CC=gcc
CFLAGS=-g -Wall -Wmissing-prototypes
LDFLAGS=-g
objects := $(patsubst %.c,%.o,$(wildcard *.c))
all: main
clean:
	-rm $(objects)
	-rm main
main: $(objects)
# gcc -MM *.c pour obtenir les deux lignes ci-dessous
liste_double.o: liste_double.c liste_double.h
main.o: main.c liste_double.h

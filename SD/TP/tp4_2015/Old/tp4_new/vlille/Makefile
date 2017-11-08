# CC		= le compilateur C à utiliser
# CFLAGS	= les options à utiliser lors de la compilation séparée
# LDFLAGS	= les options à utiliser lors de l'édition des liens
CC=gcc
CFLAGS=-g -Wall -Wmissing-prototypes -Wno-unused-function
LDFLAGS=-g
LDLIBS=-lm
# Cette instruction substitue le suffixe '.o' au suffixe '.c' dans
# tous les noms de fichiers présents dans le répertoire. 
# L'ensemble des noms de fichiers objets obtenu est affecté à objects.
objects := $(patsubst %.c,%.o,$(wildcard *.c))
# La cible principale: make
all: main
# Une autre cible: make clean
clean:
	-rm $(objects)
	-rm main
main: $(objects)
# Remplacer "main" par "bidule" si votre programme principal est "bidule.c"
# Mettre ci-dessous les lignes obtenues par gcc -MM *.c
main.o: main.c ville.h station.h priorite_station.h
priorite_station.o: priorite_station.c priorite_station.h station.h
station.o: station.c station.h
ville.o: ville.c ville.h station.h priorite_station.h


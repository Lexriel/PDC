CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS	+= -g
LDFLAGS =
EXE 	= lectureFichier codeHuffman

# $@: cible
# $^: toutes les dépendances
# $<: première dépendance

all: $(EXE)

lectureFichier: fatal.o lectureFichier.c
	$(CC) $(CFLAGS) -o $@ $^

codeHuffman: fatal.o codeHuffman.c
	$(CC) $(CFLAGS) -o $@ $^

fatal.o: fatal.c fatal.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean realclean

clean: 
	rm -rf *~ *.o 

realclean: clean
	rm -rf $(EXE)

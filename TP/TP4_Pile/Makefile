CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS	+= -g
LDFLAGS =
EXE 	= mon_wc trier_dico JeuDeLaLettreQuiSaute
DICO	= dicoTrie4lettres.h

# $@: cible
# $^: toutes les dépendances
# $<: première dépendance

all: $(EXE)

mon_wc: fatal.o readl.o mon_wc.c
	$(CC) $(CFLAGS) -o $@ $^

JeuDeLaLettreQuiSaute: fatal.o parcoursGraphe.o JeuDeLaLettreQuiSaute.c
	$(CC) $(CFLAGS) -o $@ $^

trier_dico: trier_dico.c
	$(CC) $(CFLAGS) -o $@ $^

fatal.o: fatal.c fatal.h
	$(CC) $(CFLAGS) -c $<

readl.o: readl.c fatal.c fatal.h
	$(CC) $(CFLAGS) -c $<

parcoursGraphe.o: parcoursGraphe.c parcoursGraphe.h
	$(CC) $(CFLAGS) -c $<

dicoTrie4lettres.h: trier_dico dico4lettres.h
	./$<

.PHONY: clean realclean

clean: 
	rm -rf *~ *.o 

realclean: clean
	rm -rf $(EXE) $(DICO)

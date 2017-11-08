CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS	+= -g
LDFLAGS =
EXE 	= mcu_test mcu_wc mcu_ww mcu_wl mcu_rev mcu_uniq mcu_xxd

# $@: cible
# $^: toutes les dépendances
# $<: première dépendance

all : $(EXE)

mcu_wc : mcu_affiche_entier.o mcu_wc.c
	$(CC) $(CFLAGS) -o $@ $^

mcu_ww : mcu_affiche_entier.o mcu_ww.c
	$(CC) $(CFLAGS) -o $@ $^

mcu_wl : mcu_fatal.o mcu_readl.o mcu_affiche_entier.o mcu_wl.c
	$(CC) $(CFLAGS) -o $@ $^

mcu_rev :  mcu_fatal.o mcu_readl.o mcu_rev.c
	$(CC) $(CFLAGS) -o $@ $^

mcu_uniq : mcu_fatal.o mcu_readl.o mcu_uniq.c
	$(CC) $(CFLAGS) -o $@ $^

mcu_xxd: mcu_affiche_entier.o mcu_readl.o mcu_fatal.o mcu_xxd.c
	gcc $(OPTION) -o $@ $^

mcu_test : mcu_fatal.o mcu_readl.o mcu_affiche_entier.o mcu_test.c
	$(CC) $(CFLAGS) -o $@ $^


mcu_fatal.o : mcu_fatal.c
	$(CC) $(CFLAGS) -c $^

mcu_readl.o : mcu_readl.c mcu_fatal.c mcu_fatal.h
	$(CC) $(CFLAGS) -c $<

mcu_affiche_entier.o : mcu_affiche_entier.c
	$(CC) $(CFLAGS) -c $^


.PHONY: clean realclean

clean: 
	rm -rf *.o *~ 

realclean : clean
	rm -rf $(EXE)

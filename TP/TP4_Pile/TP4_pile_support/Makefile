CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS	+= -g
LDFLAGS =
EXE 	= mcu_wc mcu_ww mcu_wl

# $@: cible
# $^: toutes les dépendances
# $<: première dépendance

all : $(EXE)

mcu_wc : mcu_wc.c
	$(CC) $(CFLAGS) -o $@ $^

mcu_ww : mcu_ww.c
	$(CC) $(CFLAGS) -o $@ $^

mcu_wl : fatal.o readl.o mcu_wl.c
	$(CC) $(CFLAGS) -o $@ $^

fatal.o : fatal.c
	$(CC) $(CFLAGS) -c $^

readl.o : readl.c fatal.c fatal.h
	$(CC) $(CFLAGS) -c $<

trier_dico.o : trier_dico.c dico4lettres.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean realclean

clean:
	rm -rf *.o *~ 

realclean : clean
	rm -rf $(EXE)

CC      = gcc
CFLAGS  = -Wall -ansi -pedantic #-Werror
CFLAGS	+= -g
LDFLAGS = # -lm
EXE 	= test_qsort test_structNobel test_qsort_int msort

# $@: cible
# $^: toutes les dépendances
# $<: première dépendance

all: $(EXE)

msort: quicksort.o readl.o fatal.o msort.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_qsort: quicksort.o structNobel.o readl.o fatal.o test_qsort.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_qsort_int: quicksort_int.o quicksort.o structNobel.o readl.o fatal.o test_qsort_int.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_structNobel: structNobel.o readl.o fatal.o test_structNobel.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

quicksort.o: quicksort.c quicksort.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

quicksort_int.o: quicksort_int.c quicksort_int.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

structNobel.o: structNobel.c readl.c fatal.c structNobel.h readl.h fatal.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

readl.o: readl.c fatal.c fatal.h readl.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

fatal.o: fatal.c fatal.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

.PHONY: clean realclean

clean: 
	rm -rf *.o *~ 

realclean: clean
	rm -rf $(EXE)

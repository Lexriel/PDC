OPTION= 

.PHONY: all 

all: bmp.o contour bruiteur

bmp.o: bmp.c bmp.h
	gcc $(OPTION) -c bmp.c

contour: bmp.o contour.c bmpf.h bmp.h
	gcc $(OPTION) -o contour bmp.o contour.c
	
bruiteur: bmp.o bruiteur.c bmpf.h bmp.h
	gcc $(OPTION) -o bruiteur bmp.o bruiteur.c

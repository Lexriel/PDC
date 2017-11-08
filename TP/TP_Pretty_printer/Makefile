CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS  += -g

all: pp

pp: pp.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean realclean

clean: 
	rm -f *~

realclean: clean
	rm -f pp

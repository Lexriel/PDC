CC=gcc
CFLAGS= -Wall -Werror -ansi -pedantic
CFLAGS+= -g

.Phony : clean

pp : pp.c
	$(CC) $(CFLAGS) -o pp pp.c

clean :
	- rm pp *.o *~

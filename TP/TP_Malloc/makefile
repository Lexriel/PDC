CFLAGS  = -Wall -Werror -ansi -pedantic -D_XOPEN_SOURCE=500
CFLAGS  += -g

all: exe

malloc.o: malloc.c
	gcc $(CFLAGS) -c $<

mmalloc: main.c malloc.o
	gcc $(CFLAGS) -o $@ $^


exe: mmalloc
	./mmalloc

clean:
	rm *.o *~

realclean: clean
	rm mmalloc

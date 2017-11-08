CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS  += -g
OBJ = mcu_readl.o mcu_fatal.o tool.o

all: mcolrm mcut mlook mgrep

mgrep: mgrep.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

mlook: mlook.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

mcut: mcut.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

mcolrm: mcolrm.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

tool.o: tool.c
	$(CC) $(CFLAGS) -c $^

mcu_fatal.o: mcu_fatal.c
	$(CC) $(CFLAGS) -c $^

mcu_readl.o : mcu_readl.c
	$(CC) $(CFLAGS) -c $^

.PHONY: clean realclean

clean:
	rm -f *.o *~

realclean: clean 
	rm *~ *.o mcolrm mcut mlook mgrep

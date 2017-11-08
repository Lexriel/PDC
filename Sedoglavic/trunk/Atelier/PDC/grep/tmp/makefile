CC	= gcc

CFLAGS	= -Werror -Wall -ansi -pedantic
CFLAGS	+= -g

OBJ = mgrep.o util.o parse.o arbre.o automate.o readl.o
BIN = mgrep

%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ -I./src

all: mgrep 

mgrep: util.o parse.o arbre.o automate.o mgrep.o readl.o
	$(CC) $(CFLAGS) util.o parse.o arbre.o automate.o readl.o mgrep.o -o $@

.PHONY: clean realclean 

clean: 
	$(RM) $(OBJ)
realclean : clean 
	$(RM) $(BIN)

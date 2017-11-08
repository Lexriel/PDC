CC	= gcc

CFLAGS	= -Wall -Werror  -ansi -pedantic
CFLAGS	+= -g

.SUFFIXES: .o .c
.c.o: ${CC} -c ${CFLAGS} $*.c

all: pp

pp: pp.o
	$(CC) $(CFLAGS) pp.o -o $@


.PHONY: clean realclean 
clean: 
	$(RM) $(OBJ)
realclean : clean 
	$(RM) pp *.o



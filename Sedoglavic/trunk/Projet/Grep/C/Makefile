.PHONY: clean
OPTION= -g -ansi -pedantic -Wall
OBJECT= set.o mongrep.o asa.o token.o automate.o mstring.o \
transitiontable.o

GCCMACRO= -D NOVERBOSE

mongrep: ${OBJECT} Makefile
	gcc ${OPTION} ${GCCMACRO} -o $@ ${OBJECT}

asa.o: asa.c types.h token.h set.h Makefile
	gcc ${OPTION} ${GCCMACRO} -c -o $@ $<

token.o: token.c token.h Makefile
	gcc ${OPTION} ${GCCMACRO} -c -o $@ $<

automate.o: automate.c types.h set.h Makefile
	gcc ${OPTION} ${GCCMACRO} -c -o $@ $<

mongrep.o: mongrep.c types.h asa.h automate.h token.h transitiontable.h Makefile
	gcc ${OPTION} ${GCCMACRO} -c -o $@ $<

mstring.o: mstring.c Makefile
	gcc ${OPTION} ${GCCMACRO} -c -o $@ $<

set.o:set.c types.h Makefile
	gcc ${OPTION} ${GCCMACRO} -c -o $@ $<

transitiontable.o: transitiontable.c types.h erreur.h Makefile 
	gcc ${OPTION} ${GCCMACRO} -c -o $@ $<

clean:
	- rm *.o mongrep *~

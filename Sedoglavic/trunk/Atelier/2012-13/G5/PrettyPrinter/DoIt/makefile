

pp: pp.c
	gcc -o pp pp.c

.PHONY:clean test

test:
	- for i in `ls *.c` ; do  ./pp < test1.c > testresultat1.c ; echo "" ; done

clean:
	-rm pp *.o *~ testresultat*


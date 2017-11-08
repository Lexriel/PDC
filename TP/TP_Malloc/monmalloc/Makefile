PAR= -ansi -pedantic 
PAR+= -D_XOPEN_SOURCE=500 
PAR+= -D_POSIX_C_SOURCE

monmalloc_essai : monmalloc_afaire.o monmalloc_infra.o monmalloc.o monmalloc_essai.c
	gcc $(PAR) -o $@ $^

monmalloc_afaire.o: monmalloc_afaire.c
	gcc $(PAR) -c $^

monmalloc.o: monmalloc.c
	gcc $(PAR) -c $^

monmalloc_infra.o: monmalloc_infra.c
	gcc $(PAR) -c $^

clean:
	-rm monmalloc*.o monmalloc_essai

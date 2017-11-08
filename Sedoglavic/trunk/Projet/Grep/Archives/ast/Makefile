.PHONY: clean


asttest: token.o ast.o test.o
	cc -g -o asttest token.o ast.o test.o
token.o: token.h token.c
	cc -g -c token.c
ast.o: ast.h ast.c 
	cc -g -c ast.c
test.o: test.c
	cc -g -c test.c

clean:
	-rm asttest *.o

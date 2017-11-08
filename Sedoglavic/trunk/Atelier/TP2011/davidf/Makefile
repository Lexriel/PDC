CC = gcc -g -Wall -Werror -pedantic -ansi
SRC = src
OUT = pp
FILE = pp.c
ARCH = pp

compile:
	$(CC) -o $(OUT) $(SRC)/$(FILE)

run:
	./$(OUT)<$(SRC)/file.c>file-i.c 2>error

clean: 
	rm $(SRC)/*#

tar:
	tar -cvzf $(ARCH).tgz $(SRC) Makefile pp LisezMoi.txt

ret:
	echo $? 

CC=gcc -g -Wall -Werror -pedantic -ansi

MAIN= src

CFLAGS= #-I/usr/include/OGRE
LDFLAGS= #-lOgreMain
SRC= $(wildcard $(MAIN)/*.c)
OBJ= $(addprefix bin/,$(notdir $(SRC:.c=.o))) 
VPATH= $(MAIN) #:$(PROG3D)

OUT= pp

NAME= foo
EXT= .tgz

auto: compile

all: clean compile run
.phony: clean

run:
	./$(OUT) < file.c

compile: $(OBJ)
	$(CC) $(LDFLAGS) -o $(OUT) $^

bin/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf ./bin/*
	rm -f $(OUT)
	find ./src/ -name '*~' -delete
	rm -f $(NAME)$(EXT)

tar: clean
	tar cvzf $(NAME)$(EXT) src/ Makefile README

CC=gcc -g -Wall -Werror -pedantic -ansi
SC=$(CC) -fsyntax-only

SRCDIR= src
BINDIR= bin
SRCDIRS= $(shell ls $(SRCDIR))

MAINDIR= $(SRCDIR)/main
VPATH= $(shell echo -n "$(CDIR)" | tr ' ' ':')
CDIR= $(addprefix $(SRCDIR)/,$(SRCDIRS))

CFLAGS= $(addprefix -I,$(CDIR))
LDFLAGS= 
SRC= $(foreach DIR,$(CDIR),$(wildcard $(DIR)/*.c))
OBJ= $(addprefix $(BINDIR)/,$(notdir $(SRC:.c=.o))) 

OUT= $(notdir $(subst .c,,$(wildcard $(MAINDIR)/*.c)))
ARGS= 

TP=$(shell basename `pwd`)
NAME= $(TP)_cavelier
EXT= .tar.gz

.phony: auto
auto: compile
all: clean compile run

check-syntax:
	$(SC) $(CFLAGS) $(SRC)

run:
	./$(OUT) $(ARGS)

compile: $(OBJ)
	$(CC) $(LDFLAGS) -o $(OUT) $^

$(BINDIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf ./bin/*
	rm -f $(OUT)
	find ./src/ -name '*~' -delete
	rm -f $(NAME)$(EXT)

tar: clean
	tar cvaf ../$(NAME)$(EXT) -C ../ $(TP)

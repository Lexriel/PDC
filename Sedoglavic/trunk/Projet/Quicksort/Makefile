OPTION = -Wall -ansi -pedantic

.PHONY: clean all

all: mqsort Quicksort.pdf

Quicksort.pdf:
	pdflatex Quicksort.tex

mqsort: quicksort.c
	gcc ${OPTION} -o mqsort quicksort.c

clean:
	- rm mqsort a.out *.aux *.log *.pdf

ifeq ($(shell uname),Darwin)
	INDENTOPTION= 
else
	INDENTOPTION=-gnu -st -nut
endif

.PHONY: clean


TeX/%.tex C/%.c : NoWeb/%.nw
	notangle -t8 -R* $< | cpif C/$(basename $*).c
	noweave -n -delay $< | cpif TeX/$(basename $*).tex

Verbatim/%.c.verb : C/%.c
	echo "\\\begin{verbatim}" > $@
	indent $(INDENTOPTION) < $< >> $@
	echo "\\\end{verbatim}" >> $@

SOURCEFILES=$(shell ls NoWeb/)
TEXTARGETS=$(addsuffix .tex,$(addprefix TeX/,$(basename $(SOURCEFILES))))
VERBTAGETS=$(addprefix Verbatim/, $(addsuffix .verb,$(notdir $(shell ls C/*.c))))

all: $(TEXTARGETS) $(VERBTAGETS)

clean:
	-rm a.out *.dvi *.log *.bbl *.blg *.aux *.h* *.gif *.image.*
	-rm *~ */*~
	-rm */a.out */*.log
	-rm *.pdf

DOC=main
HTMLDEST=$(HOME)/Enseignement/C/Web
PWD=$(shell pwd)

install: tex Verbatim/* html
	mv *.html $(HTMLDEST)/
	mv $(DOC)*.gif $(HTMLDEST)/
	mv next_motif.gif $(HTMLDEST)/
	mv previous_motif.gif $(HTMLDEST)/
	mv contents_motif.gif $(HTMLDEST)/
	cp Stuff/ustl.ps.gif $(HTMLDEST)/
	-rm $(DOC)*.h* $(DOC).log $(DOC).idx $(DOC)*.image.tex *~

tex:
	latex $(DOC).tex
	bibtex $(DOC)
	latex $(DOC).tex
tar:
	tar cvf $(DOC).tar $(PWD)

Verbatim/%.verb:        Sources/%
	echo "\begin{verbatim}" > $@
	cat $< >> $@
	echo "\end{verbatim}" >> $@

html:   Verbatim/*
	hevea -francais Stuff/macro.hva $(DOC).tex
	hevea -francais Stuff/macro.hva $(DOC).tex
	- imagen $(DOC)
	hacha -o TP.html -tocbis $(DOC).html
clean:
	-rm Sources/a.out Sources/*~
	-rm *.idx a.out *~ *.dvi *.log *.bbl *.blg *.aux *.h* *.gif *.image.*
	-rm $(DOC).dvi
	-rm TeX/*~ TeX/*.log 


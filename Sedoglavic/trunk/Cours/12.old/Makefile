REP=$(shell basename `pwd`)
DIRPATH= $(shell dirname `pwd`)
TARGETPATH=$(shell dirname $(DIRPATH))/Web
DOC=Cours

doit: 
	 sed "s/XX/$(REP)/" ../tex.model> $(DOC)$(REP).tex
	pdflatex $(DOC)$(REP).tex
	pdflatex $(DOC)$(REP).tex
	pdfnup --nup 2x3 $(DOC)$(REP).pdf
	mv $(DOC)$(REP).pdf $(TARGETPATH)/
	mv $(DOC)$(REP)-2x3.pdf $(TARGETPATH)/
	rm -f $(DOC)$(REP).*  *~
	


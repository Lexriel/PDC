.PHONY: clean
LATEXDOC=grep
TARGETPATH=../../../Web/


${TARGETPATH}${LATEXDOC}.pdf: ${LATEXDOC}.tex automate.tex Makefile
	pdflatex $< 
	pdflatex $<
	cp ${LATEXDOC}.pdf ${TARGETPATH}/

grep.ps: grep.tex automate.tex
	latex grep
	latex grep
	dvips -o grep.ps grep.dvi
clean:
	- rm *~ ${LATEXDOC}.pdf ${LATEXDOC}.log 
	- rm ${LATEXDOC}.rel ${LATEXDOC}.aux ${LATEXDOC}.dvi

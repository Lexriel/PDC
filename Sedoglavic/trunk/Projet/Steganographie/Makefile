TARGETPATH = $(HOME)/public_html/C

all: $(TARGETPATH)/steganographie.pdf

$(TARGETPATH)/steganographie.pdf: steganographie.tex 
	latex steganographie.tex
	latex steganographie.tex
	pdflatex steganographie.tex
	dvips steganographie.dvi -o tmp.ps
	psnup -2 tmp.ps > steganographie.ps
	rm tmp.ps steganographie.log steganographie.dvi steganographie.aux 
	mv steganographie.p* $(TARGETPATH)/.


DIRPATH = $(shell dirname `pwd`)
TARGETPATH = $(DIRPATH)/Web
FOLDERS=$(shell ls -d [0-9][0-9])
TODO=$(addprefix $(TARGETPATH)/Cours, $(addsuffix .pdf, $(FOLDERS)))

$(TARGETPATH)/Cours%.pdf: %/
	cp filemake $(dir $<)/Makefile
	make -C $(dir $<)/ doit 
	rm $(dir $<)/Makefile

.PHONY: all clean 

all: $(TODO)

clean:
	-rm */*~


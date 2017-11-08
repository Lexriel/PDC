TARGET= $(addsuffix Test,$(basename $(notdir $(shell ls ../NoWeb/))))


%Test: %.o %Test.c
	gcc -o $@ $?

.PHONY:clean all

all: $(TARGET)

clean:
	-rm *~ a.out *.o $(TARGET)

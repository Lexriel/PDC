CC=gcc
FLAGS=-Wall -Werror -ansi -pedantic

mcolrm:mcolrm.o readl.o tools.o
	$(CC) $(FLAGS) -o mcolrm mcolrm.o readl.o tools.o
mcut :mcut.o readl.o tools.o
	$(CC) $(FLAGS) -o mcut mcut.o readl.o tools.o
mlook:mlook.o readl.o tools.o
	$(CC) $(FLAGS) -o mlook mlook.o tools.o readl.o
mgrep:mgrep.o readl.o tools.o
	$(CC) $(FLAGS) -o mgrep mgrep.o tools.o readl.o
mlook.o:mlook.c
	$(CC) $(FLAGS) -c -o mlook.o mlook.c
mgrep.o:mgrep.c
	$(CC) $(FLAGS) -c -o mgrep.o mgrep.c
mcut.o:mcut.c
	$(CC) $(FLAGS) -c -o mcut.o mcut.c

tools.o:tools.c
	$(CC) $(FLAGS) -c -o tools.o tools.c

readl.o:readl.c
	$(CC) $(FLAGS) -c -o readl.o readl.c

mcolrm.o:mcolrm.c
	$(CC) $(FLAGS) -c -o mcolrm.o mcolrm.c
clean:
	rm *.o mcolrm mcut

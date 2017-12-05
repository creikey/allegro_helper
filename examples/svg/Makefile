
.PHONY: clean

a.out: main.o
	gcc main.o `pkg-config --libs operomnia`

main.o: main.c Makefile
	gcc -c main.c

clean:
	-rm main.o
	-rm a.out

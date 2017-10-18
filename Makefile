a.out: main.o al_helper.o
	gcc -Wall -g main.o al_helper.o -lallegro

main.o: main.c
	gcc -c main.c

al_helper.o: al_helper.c al_helper.h
	gcc -c al_helper.c

clean:
	rm *.o
	rm *.out

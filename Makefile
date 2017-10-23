OBJ = al_helper.o
LIBNAME = al_helper.zip

a.out: main.o al_helper.o
	gcc -Wall -o a.out main.o al_helper.o -lallegro -lallegro_primitives

export: $(OBJ)
	mkdir al_helper
	cp al_helper.o al_helper
	cp al_helper.h al_helper
	zip $(LIBNAME) al_helper/*
	rm -r al_helper

debug: main.o al_helper.o
	gcc -Wall -o a.out main.o al_helper.o -lallegro -lallegro_primitives -g

main.o: main.c
	gcc -c main.c

al_helper.o: al_helper.c al_helper.h
	gcc -c al_helper.c

clean:
	-rm -r al_helper
	-rm al_helper.zip
	-rm *.o
	-rm *.gch
	-rm *.out

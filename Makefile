OBJ = camengine.o
LIBNAME = camengine.a

a.out: main.o $(OBJ)
	gcc -Wall -o a.out main.o $(OBJ) -lallegro -lallegro_primitives

export: $(OBJ)
	ar ruv $(LIBNAME) $(OBJ)

debug: main.o $(OBJ)
	gcc -Wall -o a.out main.o $(OBJ) -lallegro -lallegro_primitives -g

main.o: main.c
	gcc -c main.c

camengine.o: camengine.c camengine.h
	gcc -c camengine.c
clean:
	-rm $(LIBNAME)
	-rm *.o
	-rm *.gch
	-rm *.out

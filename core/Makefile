#All of the object files
OBJ = main.o operomnia.o vectors.o mouse.o keyboard.o file.o
FILENAME =operomnia

#Includes should only be one thing
INCLUDES = operomnia-1

.PHONY: clean

engine: $(OBJ)
	gcc $(OBJ) -o $(FILENAME) $(shell pkg-config --libs --static allegro-static-5 allegro_primitives-static-5)

export: engine
	mv $(FILENAME) ..

file.o: file.c $(INCLUDES)/file.h
	gcc -c file.c

keyboard.o: keyboard.c $(INCLUDES)/keyboard.h
	gcc -c keyboard.c

mouse.o: mouse.c $(INCLUDES)/mouse.h
	gcc -c mouse.c

main.o: main.c
	gcc -c main.c

operomnia.o: operomnia.c $(INCLUDES)/operomnia.h
	gcc -c operomnia.c

vectors.o: vectors.c $(INCLUDES)/vectors.h
	gcc -c vectors.c

clean:
	-rm *.o
	-rm $(FILENAME)
	-rm *.gch
	-rm $(INCLUDES)/*.gch
	-rm *.out

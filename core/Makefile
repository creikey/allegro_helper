#All of the object files
OBJ = operomnia.o vectors.o

#Includes should only be one thing
INCLUDES = operomnia-1

LIBNAME = liboperomnia.a

.PHONY: clean

export: $(LIBNAME)
	mv $(LIBNAME) ..
	cp -r $(INCLUDES) ..

install: export
	sudo mv ../$(LIBNAME) /usr/lib
	sudo chmod 0755 /usr/lib/$(LIBNAME)
	sudo mv ../$(INCLUDES) /usr/include
	sudo chmod 0755 /usr/include/$(INCLUDES)
	echo "Successfully installed!"

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

operomnia.o: operomnia.c $(INCLUDES)/operomnia.h
	gcc -c operomnia.c

vectors.o: vectors.c $(INCLUDES)/vectors.h
	gcc -c vectors.c

clean:
	-rm $(LIBNAME)
	-rm *.o
	-rm *.gch
	-rm $(INCLUDES)/*.gch
	-rm *.out

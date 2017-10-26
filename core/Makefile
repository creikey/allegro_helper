#All of the object files
OBJ = operomnia.o vectors.o

LIBALLEG = liballeg.a

#Includes should only be one thing
INCLUDES = operomnia-1

LIBNAME = liboperomnia.a

.PHONY: clean

export: $(LIBNAME)
	mv $(LIBNAME) ..
	cp -r $(INCLUDES) ..

install: export allegro_extract
	sudo mv ../$(LIBNAME) /usr/lib
	sudo chmod 0755 /usr/lib/$(LIBNAME)
	sudo cp -r ../$(INCLUDES) /usr/include
	rm -r ../$(INCLUDES)
	#sudo mv ../$(INCLUDES) /usr/include
	sudo chmod 0755 /usr/include/$(INCLUDES)
	sudo ldconfig
	echo "Successfully installed!"

allegro_extract: export


$(LIBNAME): $(OBJ)
	-mkdir library
	cp $(OBJ) library
	cp $(LIBNAME) library
	cd library
	ar -x $(LIBNAME)
	ar -qc $(LIBNAME) *.o
	mv $(LIBNAME) ..
	cd ..
	rm -r library

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

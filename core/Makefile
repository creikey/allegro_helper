#All of the object files
OBJ = main.o operomnia.o vectors.o mouse.o keyboard.o file.o
CFILE = main.c operomnia.c vectors.c mouse.c keyboard.c file.c
WINCOMPILER = x86_64-w64-mingw32-gcc
WINFILENAME = operomnia.exe
WINZIPNAME = operomnia.zip
WINFOLDERNAME = operomnia-tmp
WININCLUDES = /home/creikey/Documents/libraries/allegro_windows/include
WINLIBS = /home/creikey/Documents/libraries/allegro_windows/lib
WINDLLS = /home/creikey/Documents/libraries/allegro_windows/bin

FILENAME = operomnia
PKGCONFIG = $(shell pkg-config --libs --static allegro-static-5 allegro_primitives-static-5)

#Includes should only be one thing
INCLUDES = operomnia-1

.PHONY: clean

engine: $(OBJ)
	gcc $(OBJ) -o $(FILENAME) $(PKGCONFIG)

windows: clean
	$(WINCOMPILER) -c -I$(WININCLUDES)  $(CFILE)
	$(WINCOMPILER) $(OBJ) -o $(WINFILENAME) -I$(WININCLUDES) -L$(WINLIBS) -lallegro -lallegro_primitives
	mkdir $(WINFOLDERNAME)
	mv $(WINFILENAME) $(WINFOLDERNAME)
	cp $(WINDLLS)/* $(WINFOLDERNAME)
	zip -r $(WINZIPNAME) $(WINFOLDERNAME)
	rm -r $(WINFOLDERNAME)



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

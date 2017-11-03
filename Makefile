# $(shell pkg-config --libs --static allegro-static-5 allegro_primitives-static-5)
# Dependant on platform
INCLUDE=/home/creikey/Documents/projects/pj_software/operomnia/include
LIBNAME=liboperomnia.a

PKG_CONFIG = src/core/liboperomnia.pc
CORE_OBJECTS = keyboard.o mouse.o operomnia.o vectors.o memory.o
CORE_C_FILES = src/core/keyboard.c \
src/core/mouse.c \
src/core/operomnia.c \
src/core/vectors.c \
src/core/memory.c
CORE_HEADERS = include/operomnia1/keyboard.h \
include/operomnia1/mouse.h \
include/operomnia1/operomnia.h \
include/operomnia1/vectors.h \
include/operomina1/memory.h

.PHONY: clean

core: $(CORE_OBJECTS)
	ar rcs $(LIBNAME) $(CORE_OBJECTS)

install: core
	sudo cp -r include/operomnia1 /usr/local/include
	sudo cp $(LIBNAME) /usr/local/lib
	sudo cp $(PKG_CONFIG) /usr/lib/pkgconfig
	sudo ldconfig

keyboard.o: src/core/keyboard.c include/operomnia1/keyboard.h
	gcc -c -I$(INCLUDE) src/core/keyboard.c

mouse.o: src/core/mouse.c include/operomnia1/mouse.h
	gcc -c -I$(INCLUDE) src/core/mouse.c

operomnia.o: src/core/operomnia.c include/operomnia1/operomnia.h
	gcc -c -I$(INCLUDE) src/core/operomnia.c

vectors.o: src/core/vectors.o include/operomnia1/vectors.h
	gcc -c -I$(INCLUDE) src/core/vectors.c

memory.o: src/core/memory.c include/operomnia1/memory.h
	gcc -c -I$(INCLUDE) src/core/memory.c

clean:
	-rm $(LIBNAME)
	-rm *.o

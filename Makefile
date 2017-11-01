# $(shell pkg-config --libs --static allegro-static-5 allegro_primitives-static-5)
# Dependant on platform
INCLUDE=/home/creikey/Documents/projects/pj_software/operomnia/include
LIBNAME=liboperomnia.a

CORE_OBJECTS = keyboard.o mouse.o operomnia.o vectors.o
CORE_C_FILES = src/core/keyboard.c \
src/core/mouse.c \
src/core/operomnia.c \
src/core/vectors.c
CORE_HEADERS = include/operomnia1/keyboard.h \
include/operomnia1/mouse.h \
include/operomnia1/operomnia.h \
include/operomnia1/vectors.h

.PHONY: clean

core: core_objects
	ar rcs $(LIBNAME) $(CORE_OBJECTS)

core_objects: $(CORE_C_FILES) $(CORE_HEADERS)
	gcc -c -I$(INCLUDE) $(CORE_C_FILES)

clean:
	-rm $(LIBNAME)
	-rm *.o

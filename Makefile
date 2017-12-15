# $(shell pkg-config --libs --static allegro-static-5 allegro_primitives-static-5)

V=1
VERSION=$(V)
INCLUDE=/home/creikey/Documents/projects/pj_software/operomnia/include
LIBNAME=liboperomnia

PKG_CONFIG = src/core/operomnia.pc
PKG_CONFIG_STATIC = src/core/operomnia_static.pc
CORE_OBJECTS = keyboard.o mouse.o operomnia.o vectors.o memory.o threads.o \
timers.o \
file.o
CORE_C_FILES = src/core/keyboard.c \
src/core/mouse.c \
src/core/operomnia.c \
src/core/vectors.c \
src/core/memory.c \
src/core/threads.c \
src/core/timers.c \
src/core/file.c
CORE_HEADERS = include/operomnia1/keyboard.h \
include/operomnia$(V)/mouse.h \
include/operomnia$(V)/operomnia.h \
include/operomnia$(V)/vectors.h \
include/operomina$(V)/memory.h \
include/operomnia$(V)/threads.h \
include/operomnia$(V)/timers.h \
include/operomnia$(V)/file.h

# DRAW_PKG_CONFIG = src/draw/liboperomnia_draw.pc
DRAW_OBJECTS = draw.o image.o sprite.o file.o
DRAW_C_FILES = src/draw/draw.c src/draw/image.c src/draw/sprite.c
DRAW_HEADERS = include/operomina1/draw/draw.h \
include/operomina1/draw/image.h \
include/operomnia1/draw/sprite.h

.PHONY: clean

core: $(CORE_OBJECTS)
	ar rcs $(LIBNAME).a $(CORE_OBJECTS)

draw: $(DRAW_OBJECTS)
	ar rcs $(LIBNAME)_draw.a $(DRAW_OBJECTS)

headers: $(CORE_HEADERS) $(DRAW_HEADERS)
	# Install the header files
	sudo cp -r include/operomnia$(V) /usr/local/include

install: headers core draw
	# Install the core library
	sudo cp $(LIBNAME).a /usr/local/lib
	sudo cp $(PKG_CONFIG) /usr/lib/pkgconfig
	sudo cp $(PKG_CONFIG_STATIC) /usr/lib/pkgconfig
	# Install the draw library
	sudo cp $(LIBNAME)_draw.a /usr/local/lib
	sudo ldconfig

uninstall:
	# Uninstalls the core library
	sudo rm /usr/local/lib/$(LIBNAME).a
	sudo rm /usr/lib/pkgconfig/$(PKG_CONFIG)
	sudo rm /usr/lib/pkgconfig/$(PKG_CONFIG_STATIC)
	# Uninstalls the draw library
	sudo rm /usr/local/lib/$(LIBNAME)_draw.a
	sudo ldconfig

file.o: src/core/file.c include/operomnia$(V)/file.h
	gcc -c -I$(INCLUDE) src/core/file.c

timers.o: src/core/timers.c include/operomnia$(V)/threads.h
	gcc -c -I$(INCLUDE) src/core/timers.c

sprite.o: src/draw/sprite.c include/operomnia1/draw/sprite.h
	gcc -c -I$(INCLUDE) src/draw/sprite.c

threads.o: src/core/threads.c include/operomnia$(V)/threads.h
	gcc -c -I$(INCLUDE) src/core/threads.c

image.o: src/draw/image.c include/operomnia$(V)/draw/image.h
	gcc  -c -I$(INCLUDE) src/draw/image.c

draw.o: src/draw/draw.c include/operomnia$(V)/draw/draw.h
	gcc -c -I$(INCLUDE) src/draw/draw.c

keyboard.o: src/core/keyboard.c include/operomnia$(V)/keyboard.h
	gcc -c -I$(INCLUDE) src/core/keyboard.c

mouse.o: src/core/mouse.c include/operomnia$(V)/mouse.h
	gcc -c -I$(INCLUDE) src/core/mouse.c

operomnia.o: src/core/operomnia.c include/operomnia$(V)/operomnia.h
	gcc -c -I$(INCLUDE) src/core/operomnia.c

vectors.o: src/core/vectors.o include/operomnia$(V)/vectors.h
	gcc -c -I$(INCLUDE) src/core/vectors.c

memory.o: src/core/memory.c include/operomnia$(V)/memory.h
	gcc -c -I$(INCLUDE) src/core/memory.c

clean:
	-rm $(LIBNAME)_draw.a
	-rm $(LIBNAME).a
	-rm *.o

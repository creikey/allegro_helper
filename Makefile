# $(shell pkg-config --libs --static allegro-static-5 allegro_primitives-static-5)
# Dependant on platform
LIBNAME=liboperomnia
NAME=operomnia
VERSION=1

PKG_CONFIG = src/core/$(NAME).pc
STATIC_PKG_CONFIG = src/core/$(NAME)_static.pc
CORE_OBJECTS = error.o keyboard.o mouse.o operomnia.o vectors.o memory.o \
threads.o \
timers.o \
file.o

MAKE_PATH=$(shell pwd)
INCLUDE=$(MAKE_PATH)/include

CORE_C_FILES = src/core/keyboard.c \
src/core/mouse.c \
src/core/operomnia.c \
src/core/vectors.c \
src/core/memory.c \
src/core/threads.c \
src/core/timers.c \
src/core/file.c \
src/core/error.c
CORE_HEADERS = include/operomnia$(VERSION)/keyboard.h \
include/operomnia$(VERSION)/mouse.h \
include/operomnia$(VERSION)/operomnia.h \
include/operomnia$(VERSION)/vectors.h \
include/operomina$(VERSION)/memory.h \
include/operomnia$(VERSION)/threads.h \
include/operomnia$(VERSION)/timers.h \
include/operomnia$(VERSION)/file.h \
include/operomnia$(VERSION)/error.h

DRAW_OBJECTS = draw.o \
image.o \
sprite.o \
file.o \
text.o \
svg.o
DRAW_C_FILES = src/draw/draw.c \
src/draw/image.c \
src/draw/sprite.c \
src/draw/text.c \
src/draw/svg.c

DRAW_HEADERS = include/operomina1/draw/draw.h \
include/operomina$(VERSION)/draw/image.h \
include/operomnia$(VERSION)/draw/sprite.h \
include/operomnia$(VERSION)/draw/text.h \
include/operomnia$(VERSION)/draw/svg.h


.PHONY: clean headers

core: $(CORE_OBJECTS)
	ar rcs $(LIBNAME).a $(CORE_OBJECTS)

draw: $(DRAW_OBJECTS)
	ar rcs $(LIBNAME)_draw.a $(DRAW_OBJECTS) $(CORE_OBJECTS)

headers:
	# Install the header files
	sudo cp -r include/$(NAME)$(VERSION) /usr/local/include

uninstall:
	# Remove header files
	-sudo rm -r /usr/local/include/$(NAME)$(VERSION)
	-sudo rm -r /usr/include/$(NAME)$(VERSION)
	# Remove the core library
	-sudo rm /usr/local/lib/$(LIBNAME).a
	-sudo rm /usr/lib/$(LIBNAME).a
	-sudo rm /usr/lib/pkgconfig/$(NAME).pc
	-sudo rm /usr/lib/pkgconfig/$(NAME)_static.pc
	# Remove the draw library
	-sudo rm /usr/lib/$(LIBNAME)_draw.a
	-sudo rm /usr/local/lib/$(LIBNAME)_draw.a
	# Recalibrate
	sudo ldconfig

install: core draw
	# Install the header files
	sudo cp -r include/$(NAME)$(VERSION) /usr/local/include
	sudo cp -r include/$(NAME)$(VERSION) /usr/include
	# Install the core library
	sudo cp $(LIBNAME).a /usr/local/lib
	sudo cp $(LIBNAME).a /usr/lib
	sudo cp $(PKG_CONFIG) /usr/lib/pkgconfig
	sudo cp $(STATIC_PKG_CONFIG) /usr/lib/pkgconfig
	# Install the draw library
	sudo cp $(LIBNAME)_draw.a /usr/lib
	sudo cp $(LIBNAME)_draw.a /usr/local/lib
	sudo ldconfig

svg.o: src/draw/svg.c include/operomnia$(VERSION)/draw/svg.h src/draw/nanosvg.h src/draw/nanosvgrast.h
	gcc -c -I$(INCLUDE) src/draw/svg.c

text.o: src/draw/text.c include/operomnia$(VERSION)/draw/text.h
	gcc -c -I$(INCLUDE) src/draw/text.c

error.o: src/core/error.c include/operomnia$(VERSION)/error.h
	gcc -c -I$(INCLUDE) src/core/error.c

file.o: src/core/file.c include/operomnia$(VERSION)/file.h
	gcc -c -I$(INCLUDE) src/core/file.c

timers.o: src/core/timers.c include/operomnia$(VERSION)/threads.h
	gcc -c -I$(INCLUDE) src/core/timers.c

sprite.o: src/draw/sprite.c include/operomnia$(VERSION)/draw/sprite.h
	gcc -c -I$(INCLUDE) src/draw/sprite.c

threads.o: src/core/threads.c include/operomnia$(VERSION)/threads.h
	gcc -c -I$(INCLUDE) src/core/threads.c

image.o: src/draw/image.c include/operomnia$(VERSION)/draw/image.h
	gcc  -c -I$(INCLUDE) src/draw/image.c

draw.o: src/draw/draw.c include/operomnia$(VERSION)/draw/draw.h
	gcc -c -I$(INCLUDE) src/draw/draw.c

keyboard.o: src/core/keyboard.c include/operomnia$(VERSION)/keyboard.h
	gcc -c -I$(INCLUDE) src/core/keyboard.c

mouse.o: src/core/mouse.c include/operomnia$(VERSION)/mouse.h
	gcc -c -I$(INCLUDE) src/core/mouse.c

operomnia.o: src/core/operomnia.c include/operomnia$(VERSION)/operomnia.h
	gcc -c -I$(INCLUDE) src/core/operomnia.c

vectors.o: src/core/vectors.o include/operomnia$(VERSION)/vectors.h
	gcc -c -I$(INCLUDE) src/core/vectors.c

memory.o: src/core/memory.c include/operomnia$(VERSION)/memory.h
	gcc -c -I$(INCLUDE) src/core/memory.c

clean:
	@rm $(LIBNAME)_draw.a ||:
	@rm $(LIBNAME).a ||:
	@rm *.o ||:

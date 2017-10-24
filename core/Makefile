OBJ = operomnia.o
LIBNAME = operomnia.a

export: $(OBJ)
	ar ruv $(LIBNAME) $(OBJ)
	mv $(LIBNAME) ..


operomnia.o: operomnia.c operomnia.h
	gcc -c operomnia.c 
clean:
	-rm $(LIBNAME)
	-rm *.o
	-rm *.gch
	-rm *.out

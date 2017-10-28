#include <stdio.h>
#include "operomnia-1/operomnia.h"
#include "operomnia-1/vectors.h"
#include "operomnia-1/file.h"

int main ( int argc, char ** arg ) {
  oprogram * my_program = new_program();
  oscript * scr_1 = new_script( "scr_1.sf" );
  oscript * scr_2 = new_script( "scr_2.sf" );
  add_script( my_program, scr_1 );
  add_script( my_program, scr_2 );
  compile_program( my_program );
  printf( "Finished compiling\n" );
  //free_scripts( my_program );
}

#include <stdio.h>
#include "operomnia-1/operomnia.h"
#include "operomnia-1/vectors.h"
#include "operomnia-1/file.h"

#include <sys/types.h>
#include <dirent.h>
#include <allegro5/allegro.h>

int main ( int argc, char ** arg ) {

  /*printf( "Printing args...\n" );
  for( int i = 0; i < argc; i++ ) {
    printf( "%d is %s\n", i, arg[i] );
  }
  return 0;*/

  printf( "Reading files...\n" );

  /*DIR *dir;
  struct dirent *sd;
  dir = opendir(".");
  if( !dir ) {
    fprintf(stderr, "ERR: NULL FILE DIRECTORY\n" );
    return -1;
  }

  while( ( sd=readdir(dir) ) != NULL ) {
    printf("dir: %s\n", sd->d_name );
  }

  closedir( dir );*/

  linker_data * l_dat = al_malloc( sizeof *l_dat );
  if( init_linker( l_dat ) ==  -1 ) {
    fprintf( stderr, "FATAL ERROR DURING LINKING\n" );
    return -1;
  }
  link_program( l_dat );

  debug_file( "main.of" );
  return 0;
}

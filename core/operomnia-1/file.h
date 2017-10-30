#ifndef H_FILE
#define H_FILE

#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>

// Struct to hold linker data
typedef struct _linker_data {
  FILE * mfp;
  DIR * my_dir;
  struct dirent *sd;
  int files;
  char * file_names[];
} linker_data;

bool file_exists( char * file_name );

void precompile_file( char * file_name, char * file_output );

int init_linker( linker_data * edit_data );

int link_program( linker_data * edit_data );

//oscript * new_script( char * file_name );

// free_scripts( oprogram * in_prog );

#endif

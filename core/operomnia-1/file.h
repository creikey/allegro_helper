#ifndef H_FILE
#define H_FILE

#include <stdio.h>

// The script struct
// Representation of .sf file
typedef struct _oscript {
  FILE * script_fp;
  char * script_file;
  struct _oscript * next_script;
} oscript;

// The program file
// Representation of a bunch of .sf files
// And the main script
typedef struct _oprogram {
  FILE * main_fp;
  oscript * script_head;
} oprogram;

int add_script( oprogram * in_prog, oscript * in_oscr );

int compile_program( oprogram * in_prog );

oscript * new_script( char * file_name );

void free_scripts( oprogram * in_prog );

oprogram * new_program( void );

#endif

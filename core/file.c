#include <stdio.h>
#include "operomnia-1/file.h"
#include <allegro5/allegro.h>

oscript * new_script( char * file_name ) {
  oscript * to_return = al_malloc( sizeof *to_return );
  to_return->script_fp = NULL;
  to_return->script_file = file_name;
  to_return->next_script = NULL;
  return to_return;
}

oprogram * new_program( void ) {
  oprogram * to_return;
  to_return = al_malloc(sizeof( *to_return ));
  return to_return;
}

void free_scripts( oprogram * in_prog ) {
  oscript * current_script;
  oscript * last_script;
  current_script = in_prog->script_head;
  while( current_script->next_script != NULL ) {
    last_script = current_script;
    current_script = current_script->next_script;
    al_free( last_script );
  }
  free( current_script );
}

int add_script( oprogram * in_prog, oscript * in_oscr ) {
  // Sees if they're null
  if( in_prog == NULL || in_oscr == NULL ) {
    fprintf( stderr, "in add script function null pointer passed\n" );
  }
  // Sets up struct to go to end of a linked list
  oscript * get_end_script  = in_prog->script_head;
  // If the head script isn't equal to null
  if( get_end_script != NULL ) {
    // Traverse the linked list until the next one is null
    while( get_end_script->next_script != NULL ) {
      get_end_script = get_end_script->next_script;
    }
    // Set it to the next one, making it null
    get_end_script = get_end_script->next_script;
  }
  // Print the FILENAME
  printf( "Appending filename %s to the program\n", in_oscr->script_file );
  // Assign the file pointer to the new script
  get_end_script = in_oscr;
}

// TODO make this function actually link
// For now all it does is append all of the oscript files to the oprogram
int compile_program( oprogram * in_prog ) {
  printf( "Linking .sf files into one .of file...\n" );
  // Make sure that the main script file is open
  in_prog->main_fp = fopen( "main.of", "w" );
  printf( "Opened main .of file...\n" );
  // Traverse the linked list of script heads
  oscript * l_traverse = in_prog->script_head;
  printf( "Preparing to traverse files..!\n" );
  while( !(l_traverse->next_script) ) {
    printf( "Iterating...\n" );
    printf( "appending oscript %s to the main\n", l_traverse->script_file );
    l_traverse->script_fp = fopen( l_traverse->script_file, "r" );
    // Append the characters
    fputc( fgetc( l_traverse->script_fp ), in_prog->main_fp );
  }
  printf( "done linking .sf files\n" );
  fclose( in_prog->main_fp );
  fclose( l_traverse->script_fp );
  return 0;
}



/*

This is an example of what the 'compiler' would do
1. Link all of the sf( script files )s into a .of( operomnia file )
2. That's it

The interpreter is later
TODO

-- SOURCE CODE --

- draw_square.sf -
// Input specifies no loop
INPUT( vector TOP_LEFT, vector BOTTOM_RIGHT )
// Draw command
draw_rect( TOP_LEFT.X, TOP_LEFT.Y, BOTTOM_RIGHT.X, BOTTOM_RIGHT.Y, c_black )

- main.sf -
#USE draw_square.sf
TOP_LEFT.X=0
TOP_LEFT.Y=0
BOTTOM_RIGHT=50
BOTTOM_RIGHT=50
draw_square(TOP_LEFT,BOTTOM_RIGHT)

-- EOF --

OUTPUT:
TOP_LEFT.X=0
TOP_LEFT.Y=0
BOTTOM_RIGHT=50
BOTTOM_RIGHT=50
draw_rect( TOP_LEFT.X, TOP_LEFT.Y, BOTTOM_RIGHT.X, BOTTOM_RIGHT.Y, c_black )
*/

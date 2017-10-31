#include <stdio.h>
#include "operomnia-1/file.h"
#include "operomnia-1/bytecode_reference.h"
#include <allegro5/allegro.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>


// TODO make this function actually link
// For now all it does is append all of the oscript files to the oprogram

// Sees if the given file exists
bool file_exists( char * file_name ) {
  if( access( file_name, F_OK ) != -1 ) {
      return true;
  }
  return false;
}

void set_string_char( char * in_char, size_t num_items, char to_set) {
  for( int i = 0; i < num_items; i++ ) {
    in_char[i] = to_set;
  }
}

error precompile_file( char * file_name, char * file_output ) {
  error to_return = { false, 0, 0 };
  FILE * f_read;
  FILE * f_out;
  f_read = fopen( file_name, "r" );
  f_out = fopen( file_output, "w" );

  //char *fgets( char *buf, int n, FILE *fp );
  // Reads one line of code
  char * str_buff = al_malloc( 256 );
  set_string_char( str_buff, 256, '\0' );
  fgets( str_buff, 255, f_read );
  // Variable to hold the current token
  const int token_size = 10;
  char * token = al_malloc(token_size);
  printf( "Clearing token with empty token\n" );
  set_string_char( token, token_size, '\0' );
  while( strlen(str_buff) > 1 ) {
    // Iterate through the line
    for( int i = 0; i < strlen(str_buff); i++ ) {
      // TODO make a precompiler using the instruction_set.txt
      if( token == "{" ) {
        fputc( OPEN_BRACKET, f_out );
        set_string_char( token, token_size, '\0' );
      } else if( token == "}" ) {
        fputc( CLOSE_BRACKET, f_out );
        set_string_char( token, token_size, '\0' );
      } else if( token == "if" ) {
        fputc( IF_STATEMENT, f_out );
        set_string_char( token, token_size, '\0' );
      } else {
        // Appends the character to the token
        int i = 0;
        for(; i < token_size; i++ ) {
          if( token[i] == '\0' ) {
            break;
          }
        }
        // Set the token character to the line index
        token[i] = str_buff[i];
      }
      /*switch( token ) {
        case "{":
          fputc( f_out, OPEN_BRACKET );
          set_string_char( token, token_size, '\0' );
          break;
        case "}":
          fputc( f_out, CLOSE_BRACKET );
          set_string_char( token, token_size, '\0' );
          break;
        case "if":
          fputc( f_out, IF_STATEMENT );
          set_string_char( token, token_size, '\0' );
          break;
        default:
          // Appends the character to the token
          int i = 0;
          for(; i < token_size; i++ ) {
            if( token[i] == '\0' ) {
              break;
            }
          }
          // Set the token character to the line index
          token[i] = str_buff[i];
          break;
      }*/
      printf( "Finished a line\n" );
    }
    // Clear the line
    set_string_char( str_buff, 256, '\0' );
    // Get another line
    fgets( str_buff, 255, f_read );
  }
  fclose( f_read );
  fclose( f_out );
}

int init_linker( linker_data * edit_data ) {
  printf( "Opening main file...\n" );
  edit_data->mfp = fopen( "main.of", "w" );
  printf( "Scanning directory for .sf files...\n" );
  edit_data->my_dir = opendir(".");
  if( edit_data->my_dir == NULL ) {
    fprintf( stderr, "ERROR: UNABLE TO OPEN DIRECTORY\n" );
    return -1;
  }
  int i = 0;
  char * dot;
  printf( "Adding scripts to list of files...\n" );
  while( ( edit_data->sd=readdir(edit_data->my_dir) ) != NULL ) {
    dot = strrchr( edit_data->sd->d_name, '.' );
    if( dot && !strcmp(dot, ".sf" ) ) {
      printf( "Found file %s...\n", edit_data->sd->d_name );
      printf( "Attempting to find %sc...\n", edit_data->sd->d_name );
      // Make a temporary variable one character longer
      size_t len = strlen(edit_data->sd->d_name);
      // One extra character for c, one for \0
      char * comp_file = al_malloc( len+1+1 );
      strcpy( comp_file, edit_data->sd->d_name );
      comp_file[len] = 'c';
      comp_file[len+1] = '\0';
      if( file_exists(comp_file) ) {
        printf( "File %s found!\n", comp_file );
      } else {
        printf( "File %s doesn't exist...Creating\n", comp_file );
        error precomp_data = precompile_file( edit_data->sd->d_name, comp_file );
        if( precomp_data.panick == true ) {
          fprintf( stderr, "ERROR: PRECOMPILER PANICK AT %d, %d\n", precomp_data.row, precomp_data.column );
        }
        printf( "File successfully compiled!\n" );
      }
      printf( "Adding file: %s to list of scripts\n", comp_file );
      // edit_data->file_names[i] = edit_data->sd->d_name;
      edit_data->file_names[i] = al_malloc( 256 );
      strcpy( edit_data->file_names[i], comp_file );
      al_free( comp_file );
      i++;
    }
  }
  edit_data->files = i;
  printf( "Done scanning for scripts!\n" );
  return 0;
}

int link_program( linker_data * edit_data ) {
  printf( "Beginning to link program...\n" );
  if( !edit_data ) {
    fprintf( stderr, "ERROR: NULL EDIT_DATA\n" );
    return -1;
  }
  printf( "Traversing through the file_names and appending them to main.of...\n" );
  FILE * current_file;
  char to_put;
  // Go through the file names and open them
  for( int i = 0; i < edit_data->files; i++ ) {
    // If the file isn't null
    if( edit_data->file_names[i] != NULL ) {
      printf( "Opening the file %s\n", edit_data->file_names[i] );
      current_file = fopen( edit_data->file_names[i], "r" );
    } else {
      printf( "String at index %d is null!\n", i );
    }
    // If it opened successfully
    if( current_file ) {
      to_put = fgetc( current_file );
      while( to_put != EOF ) {
        fputc( to_put, edit_data->mfp );
        to_put = fgetc( current_file );
      }
      printf( "Done appending file %s\n", edit_data->file_names[i] );
    } else {
      // If it didn't open
      printf( "File %s was null!\n", edit_data->file_names[i] );
    }
  }
  printf( "Done appending files...\n" );
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

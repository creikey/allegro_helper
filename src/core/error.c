#include <stdio.h>
#include <operomnia1/error.h>

void print_error( const char * to_print, const char * filename, const char * in_func, int line, bool close_message ) {
  fprintf( stderr, "\033[1;31mERROR ON LINE \033[1;33m\033[4m%d\033[0m \033[1;31m, FUNCTION \033[1;33m\033[4m%s\033[0m \033[1;31m, IN FILE \033[1;33m\033[4m%s\033[0m:\033[21;37m %s", line, in_func, filename, to_print );
  if( close_message ) {
    fprintf( stderr, "\033[0m\n");
  }
  return;
}

void print_fatal_error( const char * to_print, const char * filename, const char * in_func, int line, bool close_message ) {
  fprintf( stderr, "\033[1;33m\033[4m⚠ FATAL ERROR⚠ - \033[0m\033[1;31mERROR ON LINE %d, FUNCTION %s, IN FILE %s:\033[21;37m %s", line, in_func, filename, to_print );
  if( close_message ) {
    fprintf( stderr, "\033[0m\n");
  }
  return;
}

void print_message( const char * to_print, const char * filename, const char * in_func, int line, bool close_message ) {
  fprintf( stderr, "\033[1;33mnon-fatal log at %d, function %s in %s: \033[0m%s", line, in_func, filename, to_print );
  if( close_message ) {
    fprintf( stderr, "\n");
  }
  return;
}

void print_general_pointer( void * to_print ) {
  fprintf( stderr, "%lu", (long unsigned int)to_print );
}

void print_general_constant_string( const char * to_print ) {
  fprintf( stderr, "%s", to_print );
}

void print_general_string( char * to_print ) {
  fprintf( stderr, "%s", to_print );
}

void print_general_char( char to_print ) {
  fprintf(stderr, "%c\n", to_print );
}

void print_general_float( float to_print ) {
  fprintf(stderr, "%f", to_print);
}

void print_general_int( int to_print ) {
  fprintf(stderr, "%d", to_print);
}

void close_general_error() {
  fprintf( stderr, "\033[0m\n");
}

// Without the ending, used to print variables
/*void print_partial_fatal_error( const char * to_print, const char * filename, int line ) {
  fprintf( stderr, "\033[1;33m\033[4m⚠ FATAL ERROR⚠ - \033[0m\033[1;31mERROR ON LINE %d IN FILE %s:\033[21;37m %s", line, filename, to_print );
  return;
}*/

/*void end_error() {
  printf("\033[0m\n");
}*/
/*void print_partial_message( const char * to_print, const char * filename, int line ) {
  fprintf( stderr, "\033[1;33mnon-fatal log at line %d in %s:\033[0m %s", line, filename, to_print );
  return;
}

void continue_partial_message_float( float to_print ) {
  fprintf( stderr, "%f", to_print );
}

void continue_partial_message_integer( int to_print ) {
  fprintf( stderr, "%d", to_print );
  return;
}

void continue_partial_message( const char * to_print ) {
  fprintf( stderr, "%s", to_print );
  return;
}

void end_partial_message() {
  fprintf( stderr, "\n" );
}*/

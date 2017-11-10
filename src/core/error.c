#include <stdio.h>
#include <operomnia1/error.h>

void raise_error( int err_code, const char * function ) {
  switch( err_code ) {
    case 0:
      fprintf( stderr, "%s: ERROR: NULL POINTER\n", function );
      break;
    default:
      fprintf( stderr, "%s: ERROR: UNSPECIFIED ERROR\n", function );
      break;
  }
  return;
}

void check_if_null ( void * in_ptr, const char * in_func ) {
  if ( in_ptr == NULL ) {
    raise_error( ERR_NULL_PTR, in_func );
  }
}

#include <stdio.h>

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

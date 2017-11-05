#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <operomnia1/memory.h>
#include <operomnia1/file.h>

bool ends_with(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

char * fix_directory( const char * in_str ) {
  char * to_prepend;
  if( in_str[strlen(in_str)-1] == '/' ) {
    to_prepend = op_malloc( strlen(in_str) );
    strcpy( to_prepend, in_str );
  } else {
    to_prepend = op_malloc( strlen(in_str) + 1+1 );
    strcpy( to_prepend, in_str );
    to_prepend[ strlen(to_prepend) ] = '/';
    to_prepend[ strlen(to_prepend)+1 ] = '\0';
  }
  return to_prepend;
}

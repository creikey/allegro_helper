#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <operomnia1/error.h>
#include <operomnia1/memory.h>
#include <operomnia1/file.h>

bool ends_with(const char *str, const char *suffix) {
    //if (!str || !suffix)
    //    return 0;
    check_if_null( str, "in ends with function, str" );
    check_if_null( suffix, "in ends with function, suffix" );
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

char * fix_directory( const char * in_str ) {
  if( in_str[strlen(in_str)-1] == '/' ) {
    //char to_prepend[strlen(in_str)];
    size_t str_size = strlen( in_str ) + 1;
    char * to_prepend = op_malloc( str_size );
    memcpy( to_prepend, in_str, str_size );
    return to_prepend;
  } else {
    size_t str_size = strlen( in_str ) + 1;
    char * to_prepend = op_malloc( str_size+1 );
    memcpy( to_prepend, in_str, str_size );
    to_prepend[str_size-1] = '/';
    to_prepend[str_size] = '\0';
    return to_prepend;
  }
}

#ifndef H_ERROR
#define H_ERROR

#include <stdbool.h>

void print_error( const char * to_print, const char * filename, const char * in_func, int line, bool close_message );

void print_fatal_error( const char * to_print, const char * filename, const char * in_func, int line, bool close_message );

void print_message( const char * to_print, const char * filename, const char * in_func, int line, bool close_message );

void print_general_constant_string( const char * to_print );

void print_general_string( char * to_print );

void print_general_char( char to_print );

void print_general_float( float to_print );

void print_general_int( int to_print );

void print_general_pointer( void * to_print );

void close_general_error();

#define message(x, close) print_message( x, __FILE__, __func__, __LINE__, close );

#define error(x, close ) print_error( x, __FILE__, __func__,  __LINE__, close );

#define fatal_error(x, close ) print_fatal_error( x, __FILE__, __func__, __LINE__, close );

#define CLOSE true

#define OPEN false

#define eg_cs(x) print_general_constant_string(x)

#define eg_s(x) print_general_string(x)

#define eg_c(x) print_general_char(x)

#define eg_f(x) print_general_float(x)

#define eg_i(x) print_general_int(x)

#define eg_p(x) print_general_pointer(x)

#define eg_close() close_general_error()

#endif

#ifndef H_MEMORY
#define H_MEMORY

#include <stdio.h>

void * op_malloc( size_t to_malloc );

void op_free( void * to_free );

void * op_calloc( size_t n_items, size_t s_items );

#endif

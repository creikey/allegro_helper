#include <allegro5/allegro.h>
#include <operomnia1/memory.h>

void * op_malloc( size_t to_malloc ) {
  return al_malloc( to_malloc );
}

void * op_calloc( size_t n_items, size_t s_items ) {
  return al_calloc( n_items, s_items );
}

void op_free( void * to_free ) {
  al_free( to_free );
}

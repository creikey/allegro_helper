#include <allegro5/allegro.h>
#include <operomnia1/memory.h>

void * op_malloc( size_t to_malloc ) {
  return al_malloc( to_malloc );
}

void op_free( void * to_free ) {
  al_free( to_free );
}

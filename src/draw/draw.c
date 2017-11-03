#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <operomnia1/draw/draw.h>

op_color new_color( float r, float g, float b ) {
  return al_map_rgb( r, g, b );
}

void clear_color( op_color in_color ) {
  al_clear_to_color( in_color );
}

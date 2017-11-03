#ifndef H_DRAW
#define H_DRAW

#include <allegro5/allegro.h>

typedef ALLEGRO_COLOR op_color;

op_color new_color( float r, float g, float b );

void clear_color( op_color in_color );

#endif

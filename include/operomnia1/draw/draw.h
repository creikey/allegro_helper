#ifndef H_DRAW
#define H_DRAW

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <allegro5/allegro.h>
#include <operomnia1/vectors.h>
#include <operomnia1/draw/image.h>

typedef ALLEGRO_COLOR op_color;

op_color new_color( float r, float g, float b );

void clear_color( op_color in_color );

void draw_all( void );

void draw_line( vector start_vector, vector end_vector, op_color in_c, float in_thick );

void draw_triangle( vector v_1, vector v_2, vector v_3, op_color in_c, float in_thick );

void draw_cubic_bez( vector offset, vector p_0, vector p_1, vector p_2, vector p_3, op_color in_color, float thickness );

void draw_triangle_filled( vector v_1, vector v_2, vector v_3, op_color in_c );

void draw_rectangle( vector v_1, vector v_2, op_color in_c, float in_thick );

void draw_rectangle_filled( vector v_1, vector v_2, op_color in_c );

void draw_rounded_rectangle( vector v_1, vector v_2, vector radii, op_color in_c, float in_thick );

void draw_rounded_rectangle_filled(  vector v_1, vector v_2, vector radii, op_color in_c );

void draw_pieslice( vector middle, float r, float percent, op_color in_c, float in_thick );

#endif

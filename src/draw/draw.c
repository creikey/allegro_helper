#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <operomnia1/draw/draw.h>
#include <operomnia1/vectors.h>

op_color new_color( float r, float g, float b ) {
  return al_map_rgb( r, g, b );
}

void clear_color( op_color in_color ) {
  al_clear_to_color( in_color );
}

void draw_all( void ) {
  al_flip_display();
}

void draw_line( vector start_vector, vector end_vector, op_color in_c, float in_thick ) {
  al_draw_line( start_vector.x, start_vector.y, end_vector.x, end_vector.y, in_c, in_thick );
}

void draw_cubic_bez( vector offset, vector p_0, vector p_1, vector p_2, vector p_3, op_color in_color, float thickness ) {
  draw_line( a_v(p_0, offset), a_v(p_1, offset), in_color, thickness );
  draw_line( a_v(p_1, offset), a_v(p_2, offset), in_color, thickness );
  draw_line( a_v(p_2, offset), a_v(p_3, offset), in_color, thickness );
}

void draw_triangle( vector v_1, vector v_2, vector v_3, op_color in_c, float in_thick ) {
    al_draw_triangle( v_1.x, v_1.y, v_2.x, v_2.y, v_3.x, v_3.y, in_c, in_thick );
}

void draw_triangle_filled( vector v_1, vector v_2, vector v_3, op_color in_c ) {
  al_draw_filled_triangle( v_1.x, v_1.y, v_2.x, v_2.y, v_3.x, v_3.y, in_c );
}

void draw_rectangle( vector v_1, vector v_2, op_color in_c, float in_thick ) {
  al_draw_rectangle( v_1.x, v_1.y, v_2.x, v_2.y, in_c, in_thick );
}

void draw_rectangle_filled( vector v_1, vector v_2, op_color in_c ) {
  al_draw_filled_rectangle( v_1.x, v_1.y, v_2.x, v_2.y, in_c );
}

void draw_rounded_rectangle( vector v_1, vector v_2, vector radii, op_color in_c, float in_thick ) {
  al_draw_rounded_rectangle( v_1.x, v_1.y, v_2.x, v_2.y, radii.x, radii.y, in_c, in_thick );
}

void draw_rounded_rectangle_filled(  vector v_1, vector v_2, vector radii, op_color in_c ) {
  al_draw_filled_rounded_rectangle( v_1.x, v_1.y, v_2.x, v_2.y, radii.x, radii.y, in_c );
}

void draw_pieslice( vector middle, float r, float percent, op_color in_c, float in_thick ) {
  al_draw_pieslice( middle.x, middle.y, r, 0, 2*M_PI*percent, in_c, in_thick );
}

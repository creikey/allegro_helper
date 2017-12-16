#include <stdio.h>
#include <allegro5/allegro.h>
#include <operomnia1/vectors.h>

vector new_vector( float inx, float iny ) {
  vector return_vec;
  return_vec.x = inx;
  return_vec.y = iny;
  return return_vec;
}

void combine_vector( vector * rec, vector in ) {
  rec->x += in.x;
  rec->y += in.y;
  return;
}

vector divide_vector( vector in_v, double scalar ) {
  return v( in_v.x/scalar, in_v.y/scalar );
}

vector subtract_vectors( vector to_sub_from, vector subtractor ) {
  return new_vector( to_sub_from.x - subtractor.x, to_sub_from.y - subtractor.y );
}

vector add_vectors( vector v_1, vector v_2 ) {
  return new_vector( v_1.x+v_2.x, v_1.y+v_2.y );
}

vector multiply_vectors( vector v_1, vector v_2 ) {
  return new_vector( v_1.x*v_2.x, v_1.y*v_2.y );
}

vector divide_vectors( vector v_1, vector v_2 ) {
  return new_vector( v_1.x/v_2.x, v_1.y/v_2.y );
}

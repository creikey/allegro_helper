#ifndef H_VECTORS
#define H_VECTORS

typedef struct _vector {
  float x;
  float y;
} vector;

vector new_vector( float inx, float iny );

void combine_vector( vector * rec, vector in );

vector add_vectors( vector v_1, vector v_2 );

vector subtract_vectors( vector to_sub_from, vector subtractor );

vector multiply_vectors( vector v_1, vector v_2 );

vector divide_vectors( vector v_1, vector v_2 );

#define v new_vector
#define a_v add_vectors

#endif

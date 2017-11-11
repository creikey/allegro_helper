#ifndef H_VECTORS
#define H_VECTORS

typedef struct _vector {
  float x;
  float y;
} vector;

vector new_vector( float inx, float iny );

void combine_vector( vector * rec, vector in );

vector add_vectors( vector v_1, vector v_2 );

#endif

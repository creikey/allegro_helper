#ifndef H_VECTORS
#define H_VECTORS

typedef struct _vector {
  float x;
  float y;
} vector;

vector new_vector( float inx, float iny );

void combine_vector( vector * rec, vector in );

#endif

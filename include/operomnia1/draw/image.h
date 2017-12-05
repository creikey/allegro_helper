#ifndef H_IMAGE
#define H_IMAGE

#include <operomnia1/vectors.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct ALLEGRO_BITMAP ALLEGRO_BITMAP;

typedef struct _image {
  ALLEGRO_BITMAP * image_data;
  // Pivot point for rotation, relative to upper left corner
  vector pivot_point;
  // Original scale
  vector original_scale;
  // Scale value
  vector scale_influence;
  // Opacity
  float alpha;
  // Is it rotated?
  bool rotate;
  // Is it scaled?
  bool scale;
  // Rotation data
  float rotation;
  int draw_flags;
} image;

image * load_image( const char * filepath, bool flip_x, bool flip_y );

void rotate_image( image * in_image, float percent );

void lock_rotation( image * in_image );

void unlock_rotation( image * in_image );

void flip_image( image * in_image, bool flip_x, bool flip_y );

void free_image( image * in_image );

void scale_image( image * in_image, vector scale_fact );

void draw_image( image * in_image, vector pos );

vector get_image_dimensions( image * in_image );

void set_image_pivot_point( image * in_image, vector new_pos );

vector get_image_pivot_point( image * in_image );

#endif

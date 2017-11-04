#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <operomnia1/draw/image.h>
#include <operomnia1/memory.h>
#include <operomnia1/vectors.h>

// Loads the image and mallocs the memory
image * load_image( char * filepath, bool flip_x, bool flip_y ) {
  image * to_return = op_malloc( sizeof *to_return );
  assert( to_return->image_data = al_load_bitmap( filepath ) );
  to_return->draw_flags = 0;
  if( flip_x ) {
    to_return->draw_flags += ALLEGRO_FLIP_VERTICAL;
  }
  if( flip_y ) {
    to_return->draw_flags += ALLEGRO_FLIP_HORIZONTAL;
  }
  float w = al_get_bitmap_width(to_return->image_data);
  float h = al_get_bitmap_height(to_return->image_data);
  to_return->pivot_point.x = w/2;
  to_return->pivot_point.y = h/2;
  to_return->original_scale.x = w;
  to_return->original_scale.y = h;
  to_return->rotate = false;
  to_return->scale = false;
  to_return->rotation = 0.0;
  return to_return;
}

void rotate_image( image * in_image, float percent ) {
  in_image->rotate = true;
  in_image->rotation = 2*M_PI*percent;
}

// Changes the flip image property
void flip_image( image * in_image, bool flip_x, bool flip_y ) {
  in_image->draw_flags = 0;
  if( flip_x ) {
    in_image->draw_flags += ALLEGRO_FLIP_VERTICAL;
  }
  if( flip_y ) {
    in_image->draw_flags += ALLEGRO_FLIP_HORIZONTAL;
  }
}

// Frees the image properly
void free_image( image * in_image ) {
  al_destroy_bitmap( in_image->image_data );
  op_free( in_image );
}

void scale_image( image * in_image, float scale_fact ) {
  in_image->scale = true;
  in_image->scale_influence = scale_fact;
}

// Displays the target image with the right display flags
void draw_image( image * in_image, vector pos ) {
  if( in_image->rotate ) {
    al_draw_rotated_bitmap( in_image->image_data, in_image->pivot_point.x, in_image->pivot_point.y, pos.x, pos.y, in_image->rotation, in_image->draw_flags );
    return;
  }
  if( in_image->scale ) {
    al_draw_scaled_bitmap( in_image->image_data, \
    0,\
    0,\
    in_image->original_scale.x,\
    in_image->original_scale.y,\
    pos.x,\
    pos.y,\
    in_image->original_scale.x*in_image->scale_influence,\
    in_image->original_scale.y*in_image->scale_influence,\
    in_image->draw_flags\
  );
  return;
  }
  al_draw_bitmap( in_image->image_data, pos.x, pos.y, in_image->draw_flags );
}

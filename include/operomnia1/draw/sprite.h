#ifndef H_SPRITE
#define H_SPRITE

#include <allegro5/allegro.h>
#include <operomnia1/timers.h>

typedef struct frame {
  ALLEGRO_BITMAP * bitmap;
  char * frame_name;
  struct frame * next_frame;
} frame;

typedef struct sprite {
  op_timer * anim_timer;
  int amount_frames;
  frame * frames;
} sprite;

sprite * load_sprite( const char * sprite_dir, float in_fps );


#endif

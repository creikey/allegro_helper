#ifndef H_SPRITE
#define H_SPRITE

#include <allegro5/allegro.h>
#include <operomnia1/timers.h>

typedef struct sprite {
  op_timer * anim_timer;
  ALLEGRO_BITMAP * bitmaps[];
} sprite;

#endif

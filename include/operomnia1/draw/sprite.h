#ifndef H_SPRITE
#define H_SPRITE

#include <allegro5/allegro.h>

typedef ALLEGRO_TIMER op_timer;
typedef struct ALLEGRO_BITMAP ALLEGRO_BITMAP;

typedef struct sprite {
  op_timer * anim_timer;
  ALLEGRO_BITMAP * bitmaps[];
} sprite;

#endif

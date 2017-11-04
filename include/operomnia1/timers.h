#ifndef H_TIMERS
#define H_TIMERS

#include <allegro5/allegro.h>

typedef struct op_timer {
  ALLEGRO_TIMER * timer;
  int64_t intervals;
} op_timer;

#endif

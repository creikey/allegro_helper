#ifndef H_TIMERS
#define H_TIMERS

#include <allegro5/allegro.h>

typedef struct op_timer {
  ALLEGRO_TIMER * timer;
  int64_t intervals;
} op_timer;

op_timer * new_timer( float interval );

void start_timer( op_timer * in_timer );

void stop_timer( op_timer * in_timer );

void resume_timer( op_timer * in_timer );

void destroy_timer( op_timer * in_timer );

int64_t get_timer_count( op_timer * in_timer );

bool timer_ran( op_timer * in_timer );

#endif

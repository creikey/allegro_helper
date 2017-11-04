#include <stdio.h>
#include <operomnia1/timers.h>
#include <operomnia1/memory.h>

op_timer * new_timer( float interval ) {
  op_timer * to_return = op_malloc( sizeof *to_return );
  to_return->intervals = 0;
  to_return->timer = al_create_timer( interval );
  assert( to_return );
  return to_return;
}

void start_timer( op_timer * in_timer ) {
  al_start_timer( in_timer->timer );
}

void stop_timer( op_timer * in_timer ) {
  al_stop_timer( in_timer->timer );
}

void resume_timer( op_timer * in_timer ) {
  al_resume_timer( in_timer->timer );
}

void destroy_timer( op_timer * in_timer ) {
  al_destroy_timer( in_timer->timer );
}

int64_t get_timer_count( op_timer * in_timer ) {
  return al_get_timer_count( in_timer->timer );
}

bool timer_ran( op_timer * in_timer ) {
  if( get_timer_count(in_timer) > in_timer->intervals ) {
    in_timer->intervals = get_timer_count(in_timer);
    return true;
  } else {
    in_timer->intervals = get_timer_count(in_timer);
    return false;
  }
}

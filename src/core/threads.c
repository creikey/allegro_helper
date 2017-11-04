#include <stdio.h>
#include <operomnia1/threads.h>
#include <allegro5/allegro.h>

op_thread * create_thread( void *(*proc)(ALLEGRO_THREAD *thread, void *arg), void *arg ) {
  return al_create_thread( proc, arg );
}

void start_thread( op_thread * in_thread ) {
  al_start_thread( in_thread );
}

void stop_thread( op_thread * in_thread ) {
  // Implicitly joins with the thread and tells it to stop
  al_destroy_thread( in_thread );
}

/* Function prototype should look like this:
static void * func_thread( op_thread * thr, void * arg ) {
  while( !al_get_thread_should_stop(thr) ) {}
}
*/

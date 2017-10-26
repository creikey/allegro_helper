// /home/creikey/Documents/projects/pj_software/allegro_helper
#include <stdio.h>
#include <allegro5/allegro.h>
#include <malloc.h>
#include <operomnia-1/operomnia.h>

helper_data * my_data;
void see_if_x();

int main ( void ) {
  //helper_data * my_data = al_malloc( sizeof *my_data );
  helper_data * my_data = al_malloc( sizeof *my_data );
  al_easy_init( my_data, 400, 400, ALLEGRO_WINDOWED, 30, 25,25,25 );
  printf( "Hello, world!\n" );
  int state;
  while( true ) {
    state = al_catch_events( my_data );
    if( state == -1 ) {
      break;
    } else if( state == 1 ) {
      if( is_key_pressed(my_data, ALLEGRO_KEY_SPACE ) ) {
        printf( "space key down\n" );
      }
      if( get_mouse_pressed( my_data ).middle_button ) {
        printf( "Mouse pos: %f, %f\n", get_mouse_pos( my_data ).x, get_mouse_pos( my_data ).y );
      }
    }
  }
  al_easy_exit( my_data );
  //al_free( my_data );
  return 0;
}

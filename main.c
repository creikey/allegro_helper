// /home/creikey/Documents/projects/pj_software/allegro_helper
#include <stdio.h>
#include <allegro5/allegro.h>
#include <malloc.h>
#include "al_helper.h"

helper_data * my_data;
void see_if_x();

int main ( void ) {
  //helper_data * my_data = al_malloc( sizeof *my_data );
  helper_data * my_data = al_malloc( sizeof *my_data );
  al_easy_init( my_data, 400, 400, ALLEGRO_WINDOWED, 25,25,25 );
  printf( "Hello, world!\n" );
  while( true ) {
    if( al_catch_events( my_data ) == -1 ) {
      break;
    }
    if( is_key_down(my_data, ALLEGRO_KEY_SPACE ) ) {
      printf( "space key down\n" );
    }
    if( my_data->key_down != my_data->key_up ) {
      printf("Key pressed\n" );
    }
    if( get_mouse_pressed( my_data ).middle_button ) {
      printf( "Mouse pos: %f, %f\n", get_mouse_pos( my_data ).x, get_mouse_pos( my_data ).y );
    }
    printf( "-- game_loop --\n" );
  }
  al_easy_exit( my_data );
  //al_free( my_data );
  return 0;
}

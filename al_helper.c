#include <stdio.h>
#include <allegro5/allegro.h>
#include "al_helper.h"

#define ALLEGRO_EVENT_KEY_DOWN 11
#define ALLEGRO_EVENT_KEY_UP 12

void zero_bool( bool * in_bool, int size ) {
  for( int i = 0; i < size; i++ ) {
    in_bool[i] = false;
  }
}

void al_easy_init( helper_data * in_data, float display_x, float display_y, int display_flags, float r, float g, float b ) {
  // Make the initial variables null
  in_data->display = NULL;
  in_data->event_queue = NULL;
  // Initialize allegro
  assert( al_init() );
  // Install the keyboard and mouse
  assert( al_install_keyboard() );
  assert( al_install_mouse() );
  // Change the window's settings
  al_set_new_display_flags( display_flags );
  // Create the display and make sure it's there
  in_data->display = al_create_display( display_x, display_y );
  assert(in_data->display);
  // Create the event queue and make sure it's there
  in_data->event_queue = al_create_event_queue();
  assert(in_data->event_queue);
  // Register the display as an event source
  al_register_event_source( in_data->event_queue, al_get_display_event_source( in_data->display ) );
  // Register the keyboard and mouse as an event source
  al_register_event_source( in_data->event_queue, al_get_keyboard_event_source() );
  // Clear the display to the default colors
  in_data->clear_color = al_map_rgb(r,g,b);
  al_clear_to_color( in_data->clear_color );
  al_flip_display();
  // Done
  return;
}

void al_easy_exit( helper_data * in_data ) {
  al_destroy_display( in_data->display );
  al_destroy_event_queue( in_data->event_queue );
}

int al_catch_events( helper_data * in_data ) {
  al_get_keyboard_state( &in_data->key_state );
  ALLEGRO_EVENT  ev;
  al_get_next_event( in_data->event_queue, &ev );
  if( ev.type != 0 ) {
    if( ev.type == ALLEGRO_EVENT_KEY_DOWN ) {
      in_data->key_down = ev.keyboard.keycode;
    }
    if( ev.type == ALLEGRO_EVENT_KEY_UP ) {
      in_data->key_up = ev.keyboard.keycode;
    }
    if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
      return -1;
    }
  }
  return 0;
}

void fix_keys( helper_data * in_data ) {
  in_data->key_up = in_data->key_down;
}

vector get_mouse_pos( helper_data * in_data ) {
  vector to_return;
  al_get_mouse_state( &in_data->mouse_state );
  to_return.x = in_data->mouse_state.x;
  to_return.y = in_data->mouse_state.y;
  return to_return;
}

mouse_buttons get_mouse_buttons( helper_data * in_data ) {
  mouse_buttons to_return;
  al_get_mouse_state( &in_data->mouse_state );
  to_return.left_button = in_data->mouse_state.buttons & 1;
  to_return.right_button = in_data->mouse_state.buttons & 2;
  to_return.middle_button = in_data->mouse_state.buttons & 4;
  return to_return;
}

mouse_buttons get_mouse_pressed( helper_data * in_data ) {
  mouse_buttons to_return = empty_buttons;
  mouse_buttons current_buttons = get_mouse_buttons( in_data );
  if( current_buttons.left_button == true) {
    if( in_data->last_mouse.left_button == false ) {
      to_return.left_button = true;
      in_data->last_mouse.left_button = true;
    }
  } else {
    in_data->last_mouse.left_button = false;
  }
  if( current_buttons.right_button == true) {
    if( in_data->last_mouse.right_button == false ) {
      to_return.right_button = true;
      in_data->last_mouse.right_button = true;
    }
  } else {
    in_data->last_mouse.right_button = false;
  }
  if( current_buttons.middle_button == true) {
    if( in_data->last_mouse.middle_button == false ) {
      to_return.middle_button = true;
      in_data->last_mouse.middle_button = true;
    }
  } else {
    in_data->last_mouse.middle_button = false;
  }
  return to_return;
}

bool is_key_down( helper_data * in_data, int keycode ) {
  return al_key_down( &in_data->key_state, keycode );
}

//bool is_key_pressed( helper_data * in_data, int keycode ) {
//
//}

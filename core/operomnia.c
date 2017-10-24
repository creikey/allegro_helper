#include <stdio.h>
#include <allegro5/allegro.h>
#include "al_helper.h"

void zero_bool( bool * in_bool, int size ) {
  for( int i = 0; i < size; i++ ) {
    in_bool[i] = false;
  }
}

vector new_vector( float inx, float iny ) {
  vector return_vec;
  return_vec.x = inx;
  return_vec.y = iny;
  return return_vec;
}

void combine_vector( vector * rec, vector in ) {
  rec->x += in.x;
  rec->y += in.y;
  return;
}

void al_easy_init( helper_data * in_data, float display_x, float display_y, int display_flags, float fps, float r, float g, float b ) {
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
  // Create the timer and set the fps
  in_data->fps_time = al_create_timer( 1.0/fps );
  assert(in_data->fps_time);
  // Register the timer as an event source
  al_register_event_source( in_data->event_queue, al_get_timer_event_source( in_data->fps_time ) );
  // Register the display as an event source
  al_register_event_source( in_data->event_queue, al_get_display_event_source( in_data->display ) );
  // Register the keyboard and mouse as an event source
  al_register_event_source( in_data->event_queue, al_get_keyboard_event_source() );
  // Clear the display to the default colors
  in_data->clear_color = al_map_rgb(r,g,b);
  al_clear_to_color( in_data->clear_color );
  al_flip_display();
  // Start the fps timer
  al_start_timer( in_data->fps_time );
  // Done
  return;
}

void change_fps( helper_data * in_data, float in_fps ) {
  al_set_timer_speed( in_data->fps_time, 1.0/in_fps );
}

void al_easy_exit( helper_data * in_data ) {
  al_destroy_timer( in_data->fps_time );
  al_destroy_display( in_data->display );
  al_destroy_event_queue( in_data->event_queue );
}

// Returns -1 on display close, 0 on nothing, 1 on
int al_catch_events( helper_data * in_data ) {
  ALLEGRO_EVENT  ev;
  al_get_next_event( in_data->event_queue, &ev );
  if( ev.type != 0 ) {
    if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
      return -1;
    }
    if( ev.type == ALLEGRO_EVENT_KEY_DOWN ) {
      in_data->keys[ ev.keyboard.keycode ] = true;
    }
    if( ev.type == ALLEGRO_EVENT_KEY_UP ) {
      in_data->last_keys[ ev.keyboard.keycode ] = false;
      in_data->keys[ ev.keyboard.keycode ] = false;
    }
    if( ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty( in_data->event_queue ) ) {
      return 1;
    }
  }
  return 0;
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
  return in_data->keys[keycode];
}

bool is_key_pressed( helper_data * in_data, int keycode ) {
  if( in_data->last_keys[keycode] == false && in_data->keys[keycode] == true ) {
    in_data->last_keys[keycode] = true;
    return true;
  } else {
    return false;
  }
}

//bool is_key_pressed( helper_data * in_data, int keycode ) {
//
//}

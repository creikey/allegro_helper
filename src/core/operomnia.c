#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <operomnia1/operomnia.h>

void zero_bool( bool * in_bool, int size ) {
  for( int i = 0; i < size; i++ ) {
    in_bool[i] = false;
  }
}

void init_op( operomnia_data * in_data, float display_x, float display_y, bool anti_alias, int display_flags, float fps, float r, float g, float b ) {
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
  // Checks for anti anti_alias
  if( anti_alias ) {
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  }
  // Create the display and make sure it's there
  in_data->display = al_create_display( display_x, display_y );
  assert(in_data->display);
  // Create the event queue and make sure it's there
  in_data->event_queue = al_create_event_queue();
  assert(in_data->event_queue);
  // Create the timer and set the fps
  in_data->fps_time = al_create_timer( 1.0/fps );
  assert(in_data->fps_time);
  // Initialize allegro primitives
  al_init_primitives_addon();
  // Initialize the allegro image addon
  al_init_image_addon();
  // Initialize the font addon
  al_init_font_addon();
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

void exit_op( operomnia_data * in_data ) {
  al_destroy_timer( in_data->fps_time );
  al_destroy_display( in_data->display );
  al_destroy_event_queue( in_data->event_queue );
}

void change_fps( operomnia_data * in_data, float in_fps ) {
  al_set_timer_speed( in_data->fps_time, 1.0/in_fps );
}

bool check_run( int in_check ) {
  if( in_check == 1 ) {
    return true;
  }
  return false;
}

// Returns -1 on display close, 0 on nothing, 1 on
int catch_events( operomnia_data * in_data ) {
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

#ifndef H_AL_HELPER
#define H_AL_HELPER

#include <stdio.h>
#include <allegro5/allegro.h>
#include "vectors.h"
#include "mouse.h"

#define WINDOWED ALLEGRO_WINDOWED

typedef struct _operomnia_data {
  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT_QUEUE *event_queue;
  ALLEGRO_COLOR clear_color;
  ALLEGRO_MOUSE_STATE mouse_state;
  mouse_buttons last_mouse;
  ALLEGRO_KEYBOARD_STATE key_state;
  ALLEGRO_TIMER * fps_time;
  bool keys[ ALLEGRO_KEY_MAX ];
  bool last_keys[ ALLEGRO_KEY_MAX ];
  bool checked_keys[ALLEGRO_KEY_MAX];
} operomnia_data;

// Change the game's fps
void change_fps( operomnia_data * in_data, float in_fps );

// Will tell you if it's ok to run
bool check_run( int in_check );

// Zeros the in array of boolean
void zero_bool( bool * in_bool, int size );

// Initializes operomnia
void init_op( operomnia_data * in_data, float display_x, float display_y, int display_flags, float fps, float r, float g, float b );

// Safely exits operomnia
void exit_op( operomnia_data * in_data );

// Catches events, like keyboard presses
int catch_events( operomnia_data * in_data );

#endif

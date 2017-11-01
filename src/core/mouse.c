#include <stdio.h>
#include <allegro5/allegro.h>
#include "operomnia-1/operomnia.h"
#include "operomnia-1/mouse.h"
#include "operomnia-1/vectors.h"

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

vector get_mouse_pos( helper_data * in_data ) {
  vector to_return;
  al_get_mouse_state( &in_data->mouse_state );
  to_return.x = in_data->mouse_state.x;
  to_return.y = in_data->mouse_state.y;
  return to_return;
}

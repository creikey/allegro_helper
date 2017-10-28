#include <stdio.h>
#include <allegro5/allegro.h>
#include "operomnia-1/operomnia.h"

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

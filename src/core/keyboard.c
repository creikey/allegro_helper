#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <operomnia1/operomnia.h>
#include <operomnia1/keyboard.h>

bool is_key_down( operomnia_data * in_data, int keycode ) {
  return in_data->keys[keycode];
}

bool is_key_pressed( operomnia_data * in_data, int keycode ) {
  if( in_data->last_keys[keycode] == false && in_data->keys[keycode] == true ) {
    in_data->last_keys[keycode] = true;
    return true;
  } else {
    return false;
  }
}

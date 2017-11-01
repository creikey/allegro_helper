#ifndef H_MOUSE
#define H_MOUSE

#include <stdio.h>
#include "vectors.h"

typedef struct _mouse_buttons {
  bool left_button;
  bool right_button;
  bool middle_button;
} mouse_buttons;

typedef struct _operomnia_data operomnia_data;

static mouse_buttons empty_buttons;

mouse_buttons get_mouse_buttons( operomnia_data * in_data );

mouse_buttons get_mouse_pressed( operomnia_data * in_data );

vector get_mouse_pos( operomnia_data * in_data );

#endif

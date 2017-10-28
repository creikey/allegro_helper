#ifndef H_KEYBOARD
#define H_KEYBOARD

#include <stdio.h>

typedef struct _helper_data helper_data;

bool is_key_down( helper_data * in_data, int keycode );

bool is_key_pressed( helper_data * in_data, int keycode );

#endif

#ifndef H_KEYBOARD
#define H_KEYBOARD

typedef struct _operomnia_data operomnia_data;

bool is_key_down( operomnia_data * in_data, int keycode );

bool is_key_pressed( operomnia_data * in_data, int keycode );

#endif

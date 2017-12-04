#ifndef H_TEXT
#define H_TEXT

#include <allegro5/allegro_font.h>

#include <operomnia1/draw/draw.h>
#include <stdarg.h>

typedef struct _font {
  ALLEGRO_FONT * al_font;
} font;

font * load_font( const char * filename, int size );

void destroy_font( font * in_font );

int get_text_width( font * in_font, const char * in_str );

int get_font_height( font * in_font );

char * get_textf( const char * format, ...);

void draw_text( font * in_font, op_color in_color, vector in_pos, int flags, const char * to_draw );

void draw_textf( font * in_font, op_color color, vector pos, int flags, const char * format, ...);

#define MIDDLE_ALIGN ALLEGRO_ALIGN_CENTRE
#define LEFT_ALIGN ALLEGRO_ALIGN_LEFT
#define RIGHT_ALIGN ALLEGRO_ALIGN_RIGHT

#endif

#include <stdio.h>
#include <stdarg.h>
#include <allegro5/allegro_font.h>

#include <operomnia1/error.h>
#include <operomnia1/memory.h>
#include <operomnia1/draw/draw.h>
#include <operomnia1/draw/text.h>

font * load_font( const char * filename, int size ) {
  font * to_return = op_malloc( sizeof *to_return );
  to_return->al_font = al_load_font( filename, size, 0 );
  return to_return;
}

void destroy_font( font * in_font ) {
  al_destroy_font( in_font->al_font );
  op_free( in_font );
}

void draw_text( font * in_font, op_color in_color, vector in_pos, int flags, const char * to_draw ) {
  al_draw_text( in_font->al_font, in_color, in_pos.x, in_pos.y, flags, to_draw );
}

int get_text_width( font * in_font, const char * in_str ) {
  return al_get_text_width( in_font->al_font, in_str );
}

int get_font_height( font * in_font ) {
  return al_get_font_line_height( in_font->al_font );
}

char * get_textf( const char * format, ...) {
   ALLEGRO_USTR *buf;
   va_list ap;
   const char *s;
   if( format == NULL ) {
     error( "input text was null", CLOSE );
   }

   /* Fast path for common case. */
   if (0 == strcmp(format, "%s")) {
      va_start(ap, format);
      s = va_arg(ap, const char *);
      char * to_return = op_malloc( (strlen(s)+1) * sizeof(char) );
      memcpy(to_return,s,strlen(s)+1);
      //al_draw_text(in_font->al_font, color, pos.x, pos.y, flags, s);
      va_end(ap);
      return to_return;
   }

   va_start(ap, format);
   buf = al_ustr_new("");
   al_ustr_vappendf(buf, format, ap);
   va_end(ap);

   //al_draw_text(in_font->al_font, color, pos.x, pos.y, flags, al_cstr(buf));

   size_t cstr_size = strlen(al_cstr(buf)+1);
   char * to_return = malloc( cstr_size );
   memcpy(to_return, al_cstr(buf), cstr_size );
   al_ustr_free(buf);
   return to_return;
}

void draw_textf( font * in_font, op_color color, vector pos, int flags, const char * format, ...) {
   ALLEGRO_USTR *buf;
   va_list ap;
   const char *s;
   if( in_font == NULL ) {
     error( "font was null", CLOSE );
   }
   if( format == NULL ) {
     error( "input text was null", CLOSE );
   }

   /* Fast path for common case. */
   if (0 == strcmp(format, "%s")) {
      va_start(ap, format);
      s = va_arg(ap, const char *);
      al_draw_text(in_font->al_font, color, pos.x, pos.y, flags, s);
      va_end(ap);
      return;
   }

   va_start(ap, format);
   buf = al_ustr_new("");
   al_ustr_vappendf(buf, format, ap);
   va_end(ap);

   al_draw_text(in_font->al_font, color, pos.x, pos.y, flags, al_cstr(buf));

   al_ustr_free(buf);
}

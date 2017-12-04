#ifndef H_SVG
#define H_SVG

#include <operomnia1/vectors.h>

typedef struct _svg {
  struct NSVGimage * image;
  vector pos;
} svg;

svg * load_svg( const char * filepath );

vector get_svg_dimensions( svg * in_svg );

#endif

#ifndef H_SVG
#define H_SVG

#include <operomnia1/vectors.h>
#include <operomnia1/draw/draw.h>

typedef struct _svg {
  struct NSVGimage * image;
  //float rot;
  //vector pivot_point;
  vector scale;
  vector pos;
} svg;

void draw_svg( svg * in_svg, op_color outline_color, vector pos, float thickness );

void scale_svg( svg * in_svg, vector new_scale );

vector get_svg_scale( svg * in_svg );

vector get_svg_dimensions( svg * in_svg );

svg * load_svg( const char * filepath, int res );

vector get_svg_dimensions( svg * in_svg );

#define STANDARD_SVG_RES 96

#endif

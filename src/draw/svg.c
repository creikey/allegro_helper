#include <stdio.h>
#include <string.h>
#include <math.h>

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"

#include <operomnia1/error.h>
#include <operomnia1/operomnia.h>
#include <operomnia1/draw/draw.h>
#include <operomnia1/draw/svg.h>

svg * load_svg( const char * filepath, int res ) {
  svg * to_return = malloc ( sizeof *to_return );
  to_return->pos = new_vector(0,0);
  to_return->scale = v(1,1);
  to_return->image = nsvgParseFromFile(filepath, "px", res);
  if( to_return->image == NULL ) {
    fatal_error( "couldn't read from svg ", OPEN );
    eg_cs( filepath );
    eg_close();
  }
  return to_return;
}

void scale_svg( svg * in_svg, vector new_scale ) {
  in_svg->scale = new_scale;
}

vector get_svg_scale( svg * in_svg ) {
  return in_svg->scale;
}

vector get_svg_dimensions( svg * in_svg ) {
  return new_vector( in_svg->image->width, in_svg->image->height );
}

void draw_svg( svg * in_svg, op_color outline_color, vector pos, float thickness ) {
  NSVGshape * shape;
  NSVGpath * path;
  int i;
  for (shape = in_svg->image->shapes; shape != NULL; shape = shape->next) {
  	for (path = shape->paths; path != NULL; path = path->next) {
  		for (i = 0; i < path->npts-1; i += 3) {
  			float* p = &path->pts[i*2];
        draw_cubic_bez( pos,  v(p[0]*in_svg->scale.x,p[1]*in_svg->scale.y),v(p[2]*in_svg->scale.x,p[3]*in_svg->scale.y),v(p[4]*in_svg->scale.x,p[5]*in_svg->scale.y),v(p[6]*in_svg->scale.x,p[7]*in_svg->scale.y), outline_color, thickness );
  			//drawCubicBez(p[0],p[1], p[2],p[3], p[4],p[5], p[6],p[7]);
  		}
  	}
  }
}

void delete_svg( svg * in_svg ) {
  nsvgDelete( in_svg->image );
  free(in_svg);
}

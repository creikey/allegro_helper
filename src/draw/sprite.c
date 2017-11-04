#include <stdio.h>
#include <dirent.h>
#include <operomnia1/memory.h>
#include <operomnia1/draw/draw.h>
#include <operomnia1/draw/sprite.h>

sprite * load_sprite( char * sprite_dir, float in_fps ) {
  sprite * to_return = op_malloc( sizeof *to_return );

  DIR *dir;
  struct dirent *ent;
  if( (dir = opendir( sprite_dir ) ) != NULL ) {
    while( (ent = readdir (dir) ) != NULL ) {
      printf( "Loading frame %s\n", ent->d_name );
    }
  }

  return to_return;
}

#include <stdio.h>
#include <dirent.h>
#include <operomnia1/memory.h>
#include <operomnia1/draw/draw.h>
#include <operomnia1/draw/sprite.h>
#include <operomnia1/file.h>

void append_frame( frame * head_frame, const char * in_frame_name ) {
  frame * to_append = op_malloc( sizeof *to_append );
  frame * data = head_frame;
}

sprite * load_sprite( const char * sprite_dir, float in_fps ) {
  sprite * to_return = op_malloc( sizeof *to_return );

  char * to_prepend;
  if( sprite_dir[strlen(sprite_dir)-1] == '/' ) {
    to_prepend = op_malloc( strlen(sprite_dir) );
    strcpy( to_prepend, sprite_dir );
  } else {
    to_prepend = op_malloc( strlen(sprite_dir) + 1+1 );
    strcpy( to_prepend, sprite_dir );
    to_prepend[ strlen(to_prepend) ] = '/';
    to_prepend[ strlen(to_prepend)+1 ] = '\0';
  }
  printf( "Opening dir %s\n", to_prepend );

  DIR *dir;
  int frames = 0;
  struct dirent *ent;
  if( (dir = opendir( sprite_dir ) ) != NULL ) {
    while( (ent = readdir (dir) ) != NULL ) {
      printf( "Reading file %s\n", ent->d_name );
      if( ends_with(ent->d_name, ".png" ) ) {
        printf( "Frame found at %s\n", ent->d_name );
        char * result = op_malloc( strlen(ent->d_name)+strlen(to_prepend)+1 );
        strcpy( result, to_prepend );
        strcat( result, ent->d_name );
        printf( "Appending frame %s...\n", result );
        frames += 1;



        op_free( result );
      }
    }
  } else {
    printf( "Dir %s was null!\n", to_prepend );
  }
  op_free( to_prepend );
  return to_return;
}

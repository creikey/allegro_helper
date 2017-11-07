#include <stdio.h>
#include <dirent.h>
#include <operomnia1/memory.h>
#include <operomnia1/draw/draw.h>
#include <operomnia1/draw/image.h>
#include <operomnia1/draw/sprite.h>
#include <operomnia1/file.h>
#include <operomnia1/error.h>

frame * create_header_frame( const char * in_frame_path ) {
  // Create the initial memory
  frame * to_return = op_malloc( sizeof *to_return );
  //Initialize the values
  //printf( "Reading file %s\n", in_frame_path );
  to_return->frame_data = al_load_bitmap( in_frame_path );
  assert( to_return->frame_data );
  //assert( to_return->frame_data = al_load_bitmap( in_frame_path ) );
  //assert( to_return->frame_data = al_load_bitmap( "test/3.png" ) );
  to_return->frame_name = op_malloc( strlen(in_frame_path)+1 );
  strcpy( to_return->frame_name, in_frame_path );
  to_return->next_frame = NULL;
  return to_return;
}

void append_frame( frame * head_frame, char * in_frame_path ) {
  if( head_frame == NULL || in_frame_path == NULL ) {
    raise_error( ERR_NULL_PTR, "ln 27 append_frame" );
  }
  // Create the main frame to append
  frame * to_append = op_malloc( sizeof *to_append );
  // Set the frame's path to the input path
  size_t size_path = (strlen( in_frame_path )+1) * ( sizeof(char) );
  to_append->frame_name = op_malloc( size_path );
  memcpy( to_append->frame_name, in_frame_path, size_path );
  //assert( to_append->frame_data = al_load_bitmap( in_frame_path ) );
  // Make sure that the directory is valid
  to_append->frame_data = al_load_bitmap( in_frame_path );
  // Create the pointer to traverse the linked list of frames
  frame * data = head_frame;
  // Traverse the linked list
  while( data->next_frame != NULL ) {
    data = data->next_frame;
  }
  // Actually append the frame
  data->next_frame = to_append;
}

void read_frames( frame * head_frame ) {
  if( head_frame == NULL ) {
    fprintf( stderr, "ERROR: FRAME WAS NULL\n" );
    return;
  }
  printf( "Reading frames...\n" );
  int index = 0;
  frame * data = head_frame;
  while( data->next_frame != NULL ) {
    printf( "Frame at index %d: %s\n", index, data->frame_name );
    data = data->next_frame;
    index += 1;
  }
  //printf( "Frame at index %d: %s\n", index, data->frame_name );
  printf( "Done reading frames!\n" );
}

sprite * load_sprite( const char * sprite_dir, float in_fps ) {
  // Create the initial memory for the sprite
  sprite * to_return = op_malloc( sizeof *to_return );
  // Set some base values
  to_return->current_frame = 0;
  to_return->amount_frames = 0;
  to_return->frames = NULL;

  // Make the directory better
  const char * to_prepend = fix_directory( sprite_dir );
  //printf( "Opening dir %s\n", to_prepend );
  // Basic datatypes to look in the directory
  DIR *dir;
  struct dirent *ent;
  // If the directory exists
  if( (dir = opendir( sprite_dir ) ) != NULL ) {
    // While the file in the directory isn't null
    while( (ent = readdir (dir) ) != NULL ) {
      //printf( "Reading file %s\n", ent->d_name );
      // If it's a .png file
      if( ends_with(ent->d_name, ".png" ) ) {
        //printf( "Frame found at %s\n", ent->d_name );
        // Create the string for the frame to load
        char * result = op_malloc( strlen(ent->d_name)+strlen(to_prepend)+3 );
        //strcpy( result, to_prepend );
        strcpy( result, to_prepend );
        strcat( result, ent->d_name );
        //printf( "Appending frame %s...\n", result );
        if( to_return->frames == NULL ) {
          to_return->frames = create_header_frame( result );
        } else {
          append_frame( to_return->frames, result );
        }
        op_free( result );
      }
    }
  } else {
    printf( "Dir %s was null!\n", to_prepend );
  }
  op_free( (char*)to_prepend );
  return to_return;
}

#include <stdio.h>
#include <dirent.h>
#include <operomnia1/memory.h>
#include <operomnia1/draw/draw.h>
#include <operomnia1/draw/image.h>
#include <operomnia1/draw/sprite.h>
#include <operomnia1/timers.h>
#include <operomnia1/file.h>
#include <operomnia1/error.h>

int get_frame_numb( char * in_path ) {
  return char_to_numb(\
    in_path[\
    get_strchar_index(in_path, '.', true)-1\
    ]
  );
}

void free_frames( frame * in_frame ) {
  check_if_null( in_frame, "error freeing frames, in frame was null" );
  frame * to_destroy = in_frame;
  frame * to_free;
  while( to_destroy->next_frame != NULL ) {
    al_destroy_bitmap( to_destroy->frame_data );
    op_free( to_destroy->frame_name );
    to_free = to_destroy;
    to_destroy = to_destroy->next_frame;
    op_free( to_free );
  }
  al_destroy_bitmap( to_destroy->frame_data );
  op_free( to_destroy->frame_name );
  op_free( to_destroy );
}

void destroy_sprite( sprite * in_sprite ) {
  check_if_null( in_sprite, "error freeing sprite, sprite was null" );
  destroy_timer( in_sprite->anim_timer );
  free_frames( in_sprite->frames );
  op_free( in_sprite );
}

frame * create_header_frame( const char * in_frame_path ) {
  // Create the initial memory
  frame * to_return = op_calloc( 1, sizeof *to_return );
  check_if_null( to_return, "create header frame" );
  //Initialize the values
  printf( "--- Reading file %s\n", in_frame_path );
  to_return->frame_data = al_load_bitmap( in_frame_path );
  check_if_null( to_return->frame_data, "loading frame data in create_header_frame" );
  //assert( to_return->frame_data = al_load_bitmap( in_frame_path ) );
  //assert( to_return->frame_data = al_load_bitmap( "test/3.png" ) );
  to_return->frame_name = op_malloc( strlen(in_frame_path)+1 );
  memcpy( to_return->frame_name, in_frame_path, strlen(in_frame_path)+1 );
  //strcpy( to_return->frame_name, in_frame_path );
  //to_return->frame_name[ strlen( in_frame_path) ] = '\0';
  to_return->next_frame = NULL;
  printf( "Successfully create header frame for %s\n", to_return->frame_name );
  to_return->frame_numb = get_frame_numb( (char*)in_frame_path );
  return to_return;
}

// You just need a number before the .png
void sort_frames( frame * head_frame ) {

}

void append_frame( frame * head_frame, char * in_frame_path ) {
  if( head_frame == NULL || in_frame_path == NULL ) {
    raise_error( ERR_NULL_PTR, "ln 30 append_frame" );
  }
  // Create the main frame to append
  frame * to_append = op_calloc( 1, sizeof *to_append );
  // Set the frame's path to the input path
  size_t size_path = (strlen( in_frame_path )+1) * ( sizeof(char) );
  to_append->frame_name = op_malloc( size_path );
  memcpy( to_append->frame_name, in_frame_path, size_path );
  //assert( to_append->frame_data = al_load_bitmap( in_frame_path ) );
  printf( "--- Appending frame %s...\n", to_append->frame_name );
  // Make sure that the directory is valid
  to_append->frame_data = al_load_bitmap( in_frame_path );
  check_if_null( to_append->frame_data, "append_frame frame_data" );
  // Create the pointer to traverse the linked list of frames
  frame * data = head_frame;
  int index = 0;
  // Traverse the linked list
  while( data->next_frame != NULL ) {
    data = data->next_frame;
    printf( "Cycling through frame %s index %d\n", in_frame_path, index );
    index += 1;
  }
  if( data == NULL ) {
    raise_error( ERR_NULL_PTR, "data was null" );
  }
  // Actually append the frame
  to_append->frame_numb = get_frame_numb( in_frame_path );
  data->next_frame = to_append;
  printf( "-!- SUCCESSFULLY APPENDED SPRITE %s -!-\n", data->next_frame->frame_name );
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
    printf( "Frame at index %d: %s, thinks it's number is %d\n", index, data->frame_name, data->frame_numb );
    data = data->next_frame;
    index += 1;
  }
  printf( "Last frame: %s, thinks it's number is %d\n", data->frame_name, data->frame_numb );
  printf( "Done reading frames!\n" );
}

sprite * load_sprite( const char * sprite_dir, float in_fps ) {
  // Create the initial memory for the sprite
  sprite * to_return = op_calloc( 1, sizeof *to_return );
  check_if_null( to_return, "load_sprite after malloc" );
  // Set some base values
  to_return->current_frame = 0;
  to_return->amount_frames = 0;
  to_return->frames = NULL;
  to_return->fps = in_fps;

  // Make the directory better
  const char * to_prepend = fix_directory( sprite_dir );
  check_if_null( (char*)to_prepend, "fix directory name" );
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
        printf( "-- Scanning with file %s --\n", ent->d_name );
        //printf( "Frame found at %s\n", ent->d_name );
        // Create the string for the frame to load
        char * result = op_malloc( strlen(ent->d_name)+strlen(to_prepend)+3 );
        //strcpy( result, to_prepend );
        strcpy( result, to_prepend );
        strcat( result, ent->d_name );
        printf( "-!- Crafted this result: %s...\n", result );
        if( to_return->frames == NULL ) {
          to_return->frames = create_header_frame( result );
        } else {
          append_frame( to_return->frames, result );
        }
        //op_free( result );
      }
    }
  } else {
    printf( "Dir %s was null!\n", to_prepend );
  }
  //op_free( (char*)to_prepend );
  return to_return;
}

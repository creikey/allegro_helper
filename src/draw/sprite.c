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
  // Make it a header frame
  to_return->is_head_frame = true;
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

void add_sorted_frame( sprite * data, frame * head_frame, char * in_frame_path ) {
  if( head_frame == NULL || in_frame_path == NULL ) {
    fprintf( stderr, "!-! Head frame or in frame path null\n" );
    return;
  }
  printf( "--- Sorting frames below...\n" );
  read_frames( head_frame );
  frame * to_add = op_calloc( 1, sizeof *to_add );
  // Fix the directory
  size_t size_path = (strlen( in_frame_path) +1) * ( sizeof(char) );
  to_add->frame_name = op_malloc( size_path );
  // Add it to the frame
  memcpy( to_add->frame_name, in_frame_path, size_path );
  // Load the sprite
  to_add->frame_data = al_load_bitmap( in_frame_path );
  check_if_null( to_add->frame_data, "failed to load bitmap" );
  // Add the frame number
  to_add->frame_numb = get_frame_numb( in_frame_path );
  // Set the next one to null
  to_add->next_frame = NULL;
  // Add the frame sorted
  frame * cur = head_frame;
  while( cur->next_frame != NULL ) {
    printf( "Cycling through frame %d to find a fit for %d\n", cur->frame_numb, to_add->frame_numb );
    // If the current frame is less than the one to add
    if( to_add->frame_numb < cur->frame_numb ) {
      printf("It was greater than\n" );
      break;
    } else {
      cur = cur->next_frame;
    }
  }
  if( cur == head_frame ) {
    if( cur->frame_numb > to_add->frame_numb ) {
      cur->is_head_frame = false;
      to_add->next_frame = cur;
      to_add->is_head_frame = true;
      data->frames = to_add;
      return;
    } else {
      cur->next_frame = to_add;
      return;
    }
  }
  if( cur->next_frame == NULL ) {
    cur->next_frame = to_add;
    return;
  } else {
    frame * to_append = cur->next_frame;
    cur->next_frame = to_add;
    to_add->next_frame = to_append;
    return;
  }
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
  to_append->is_head_frame = false;
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
  /*if( head_frame == NULL ) {
    fprintf( stderr, "ERROR: FRAME WAS NULL\n" );
    return;
  }*/
  check_if_null( head_frame, "input frame for read_frames null" );
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
          //append_frame( to_return->frames, result );
          add_sorted_frame( to_return, to_return->frames, result );
        }
        to_return->amount_frames += 1;
        //op_free( result );
      }
    }
  } else {
    printf( "Dir %s was null!\n", to_prepend );
  }
  //op_free( (char*)to_prepend );
  //sprite * really_to_return = sort_frames( to_return );
  //sprite * really_to_return = to_return;
  //to_delete( really_to_return );
  //check_if_null( really_to_return, "after sorted frames" );
  return to_return;
}

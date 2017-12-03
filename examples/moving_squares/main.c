#include <stdio.h>
#include <operomnia1/operomnia.h>
#include <operomnia1/error.h>
#include <operomnia1/draw/draw.h>

#define default_clear_color new_color(100,100,100)

void game_loop( operomnia_data * in_data );

void init_game( operomnia_data * in_data );

int main( void ) {
  operomnia_data * data = malloc( sizeof *data );
  init_op( data, 500,500, false, ALLEGRO_WINDOWED, 60, 255,255,0 );
  bool quit = false;
  init_game(data);
  while( true ) {
    int events = catch_events( data );
    switch(events) {
      case -1:
        quit = true;
        break;
      case 1:
        eg_cs("game loop running\n");
        game_loop(data);
        break;
    }
    if( quit ) {
      printf( "quitting\n" );
      break;
    }
  }
  exit_op( data );
}

void draw_square( vector in_vector ) {
  draw_rectangle_filled( in_vector, add_vectors(in_vector,new_vector(50,50)),new_color(255,0,0) );
}

void limit_square ( vector * in_vec ) {
  if( in_vec->x > 450 ) {
    in_vec->x = 450;
  } else if( in_vec->x < 0 ) {
    in_vec->x = 0;
  }
  if( in_vec->y > 450 ) {
    in_vec->y = 450;
  } else if( in_vec->y < 0 ) {
    in_vec->y = 0;
  }
}
void dampen_vel( vector * in_vel, float dampen_speed ) {
  if( in_vel->x > 0+dampen_speed ) {
    in_vel->x -= dampen_speed;
  } else if( in_vel->x < 0-dampen_speed ) {
    in_vel->x += dampen_speed;
  } else {
    in_vel->x = 0;
  }
  if( in_vel->y > 0+dampen_speed ) {
    in_vel->y -= dampen_speed;
  } else if( in_vel->y < 0-dampen_speed ) {
    in_vel->y += dampen_speed;
  } else {
    in_vel->y = 0;
  }
}

vector square_vel;
vector square_pos;

void init_game( operomnia_data * in_data ) {
  square_pos = new_vector(250,250);
}

void game_loop( operomnia_data * in_data ) {
  clear_color( default_clear_color );
  //clear_color(new_color(0,255,0));

  if( is_key_down( in_data, ALLEGRO_KEY_LEFT ) ) {
    square_vel.x -= 1;
  }
  if( is_key_down( in_data, ALLEGRO_KEY_RIGHT ) ) {
    square_vel.x += 1;
  }
  if( is_key_down( in_data, ALLEGRO_KEY_UP ) ) {
    square_vel.y -= 1;
  }
  if( is_key_down( in_data, ALLEGRO_KEY_DOWN ) ) {
    square_vel.y += 1;
  }
  if( is_key_down( in_data, ALLEGRO_KEY_G ) ) {
    square_pos = new_vector(250,250);
  }

  dampen_vel( &square_vel, 0.5 );
  combine_vector( &square_pos, square_vel );
  limit_square( &square_pos );
  draw_square( square_pos );

  draw_all();
}

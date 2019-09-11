#include <tests/graphics/spritesheets.fixture.h>

#include <yage/graphics/graphics_manager.hpp>
#include <yage/graphics/spritesheet.hpp>


enum class jewel_type
{
  YELLOW=0, GRAY, BLUE, RED, PURPLE
};

enum class jewel_animation_type 
{
  IDLE, COLLAPSING, GLOWING
};



TEST_F(spritesheet_fixture, load_sprite)
{
  using namespace yage::graphics;
  yage::graphics::graphics_manager::instance().set_window(yage::graphics::window("bejeweled", 514, 480));


  spritesheet< jewel_type, jewel_animation_type > jewels{ "assets/gems.spritesheet.transparent.png" };
  int x = 0, y = 0, w = 32, h = 32;
  jewels[ jewel_type::YELLOW ][ jewel_animation_type::IDLE ].map(x, y, w, h); 
  jewels[ jewel_type::YELLOW ][ jewel_animation_type::COLLAPSING ].map_all_of(14, x, y, w, h );
  jewels[ jewel_type::YELLOW ][ jewel_animation_type::GLOWING ].map_all_of(14, x, y+h, w, h );
  
  jewels[ jewel_type::GRAY ][ jewel_animation_type::IDLE ].map(x, y+2*h, w, h); 
  jewels[ jewel_type::GRAY ][ jewel_animation_type::COLLAPSING ].map_all_of(14, x, y+2*h, w, h );
  jewels[ jewel_type::GRAY ][ jewel_animation_type::GLOWING ].map_all_of(14, x, y+3*h, w, h );

  jewels[ jewel_type::BLUE ][ jewel_animation_type::IDLE ].map(x, y+4*h, w, h); 
  jewels[ jewel_type::BLUE ][ jewel_animation_type::COLLAPSING ].map_all_of(14, x, y+4*h, w, h );
  jewels[ jewel_type::BLUE ][ jewel_animation_type::GLOWING ].map_all_of(14, x, y+5*h, w, h );

  jewels[ jewel_type::RED ][ jewel_animation_type::IDLE ].map(x, y+6*h, w, h); 
  jewels[ jewel_type::RED ][ jewel_animation_type::COLLAPSING ].map_all_of(14, x, y+6*h, w, h );
  jewels[ jewel_type::RED ][ jewel_animation_type::GLOWING ].map_all_of(14, x, y+7*h, w, h );

  jewels[ jewel_type::PURPLE ][ jewel_animation_type::IDLE ].map(x, y+8*h, w, h); 
  jewels[ jewel_type::PURPLE ][ jewel_animation_type::COLLAPSING ].map_all_of(14, x, y+8*h, w, h );
  jewels[ jewel_type::PURPLE ][ jewel_animation_type::GLOWING ].map_all_of(14, x, y+9*h, w, h );



  auto l = 0;
  SDL_Rect y_idle_dest {  x,     y+l*h, w, h };
  SDL_Rect y_coll_dest {  x+w,   y+l*h, w, h };
  SDL_Rect y_glow_dest {  x+2*w, y+l*h, w, h };
  l++; 
  SDL_Rect g_idle_dest { x, y+l*h, w, h };
  SDL_Rect g_coll_dest { x+w, y+l*h, w, h };
  SDL_Rect g_glow_dest { x+2*w, y+l*h, w, h };
  l++; 
  SDL_Rect b_idle_dest { x, y+l*h, w, h };
  SDL_Rect b_coll_dest { x+w, y+l*h, w, h };
  SDL_Rect b_glow_dest { x+2*w, y+l*h, w, h };
  l++; 
  SDL_Rect r_idle_dest { x, y+l*h, w, h };
  SDL_Rect r_coll_dest { x+w, y+l*h, w, h };
  SDL_Rect r_glow_dest { x+2*w, y+l*h, w, h };
  l++; 
  SDL_Rect p_idle_dest { x, y+l*h, w, h };
  SDL_Rect p_coll_dest { x+w, y+l*h, w, h };
  SDL_Rect p_glow_dest { x+2*w, y+l*h, w, h };
  
  auto&& renderer = yage::graphics::graphics_manager::instance().get_window();
  
  SDL_SetRenderDrawColor(renderer,0,0,0,123);
  
  SDL_RenderClear(renderer);
  int frame = 150;
  while ( frame --> 0 )
  {
    SDL_RenderClear(renderer);
    jewels[ jewel_type::YELLOW ][ jewel_animation_type::IDLE ].render( &y_idle_dest );
    jewels[ jewel_type::YELLOW ][ jewel_animation_type::COLLAPSING ].tick();
    jewels[ jewel_type::YELLOW ][ jewel_animation_type::COLLAPSING ].render( &y_coll_dest );
    jewels[ jewel_type::YELLOW ][ jewel_animation_type::GLOWING ].tick();
    jewels[ jewel_type::YELLOW ][ jewel_animation_type::GLOWING ].render( &y_glow_dest );
    
    jewels[ jewel_type::GRAY ][ jewel_animation_type::IDLE ].render( &g_idle_dest );
    jewels[ jewel_type::GRAY ][ jewel_animation_type::COLLAPSING ].tick();
    jewels[ jewel_type::GRAY ][ jewel_animation_type::COLLAPSING ].render( &g_coll_dest );
    jewels[ jewel_type::GRAY ][ jewel_animation_type::GLOWING ].tick();
    jewels[ jewel_type::GRAY ][ jewel_animation_type::GLOWING ].render( &g_glow_dest );
    
    jewels[ jewel_type::BLUE ][ jewel_animation_type::IDLE ].render( &b_idle_dest );
    jewels[ jewel_type::BLUE ][ jewel_animation_type::COLLAPSING ].tick();
    jewels[ jewel_type::BLUE ][ jewel_animation_type::COLLAPSING ].render( &b_coll_dest );
    jewels[ jewel_type::BLUE ][ jewel_animation_type::GLOWING ].tick();
    jewels[ jewel_type::BLUE ][ jewel_animation_type::GLOWING ].render( &b_glow_dest );
    
    jewels[ jewel_type::RED ][ jewel_animation_type::IDLE ].render( &r_idle_dest );
    jewels[ jewel_type::RED ][ jewel_animation_type::COLLAPSING ].tick();
    jewels[ jewel_type::RED ][ jewel_animation_type::COLLAPSING ].render( &r_coll_dest );
    jewels[ jewel_type::RED ][ jewel_animation_type::GLOWING ].tick();
    jewels[ jewel_type::RED ][ jewel_animation_type::GLOWING ].render( &r_glow_dest );

    jewels[ jewel_type::PURPLE ][ jewel_animation_type::IDLE ].render( &p_idle_dest );
    jewels[ jewel_type::PURPLE ][ jewel_animation_type::COLLAPSING ].tick();
    jewels[ jewel_type::PURPLE ][ jewel_animation_type::COLLAPSING ].render( &p_coll_dest );
    jewels[ jewel_type::PURPLE ][ jewel_animation_type::GLOWING ].tick();
    jewels[ jewel_type::PURPLE ][ jewel_animation_type::GLOWING ].render( &p_idle_dest );



    SDL_RenderPresent(renderer);
    SDL_Delay(1000/30);
  }
}


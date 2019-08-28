#include <iostream>
#include <cassert>
#include <yage/graphics/spritesheet.hpp>
#include <yage/graphics/graphics_manager.hpp>

namespace yage {
namespace graphics {
namespace interface1 {

animation::animation(const texture& map):
  tex{ map }
, seq{}
, ticks{0}
{
  invariant();
}

void animation::map(uint32_t x, uint32_t y, uint32_t w, uint32_t h ) 
{
  const std::string name{"animation::map(uint,uint,uint,uint): "};  
  //std::cout << name << "enter" << std::endl;
  invariant();
  SDL_Rect rect;

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  //std::cout << name << "mapping { " << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << " } " << std::endl;
  seq.emplace( seq.end(), rect );
  invariant();
  //std::cout << "animation::map(uint,uint,uint,uint): exit" << std::endl;
}

void animation::map_all_of(uint32_t frames, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
  const std::string fn{"animation::map_all_of(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t): "};
  invariant();
  //std::cout << fn << "enter. mapping " << frames << "." << std::endl;
  SDL_Rect r;
  r.w = w;
  r.h = h;
  r.x = x;
  r.y = y;
  int frame_count = frames;
  while (frames --> 0)
  {
    r.x += r.w;

    //std::cout << fn << "mapping { " << r.x << ", " << r.y << ", " << r.w << ", " << r.h << " } " << std::endl;
    seq.emplace(seq.end(), r);
  }
 
  auto prev_x = seq[0].x;
  frames++;
  while (frames ++> frame_count)
  {
    assert(prev_x < seq[frames].x);
  }
  invariant();
  //std::cout << fn << "exit" << std::endl;
}


void animation::render(const SDL_Rect * d) 
{
  std::string fname{"animation::render(): "};
  invariant();
//  std::cout << fname << "enter" << std::endl;
  auto&& r = yage::graphics::graphics_manager::instance().get_window();
  SDL_Rect* o = &seq[ticks];
  //std::cout << fname << "rendering rect { " << o->x << ", " << o->y << ", " << o->w << ", " << o->h << " } into { " << d->x << ", " << d->y << ", " << d->w << ", " << d->h << " }" << std::endl;

  SDL_RenderCopy(r, tex, o, d); 
//  std::cout << fname << "exit" << std::endl;
  invariant();
}

void animation::render(int32_t x, int32_t y, int32_t w, int32_t h)
{
  using yage::graphics::graphics_manager;
  invariant();
  auto&& renderer = graphics_manager::instance().get_window();
  SDL_Rect *s = &(seq[ticks]);
  SDL_Rect d{ .x = x, .y = y, .w = w, .h = h };
  SDL_RenderCopy(renderer, tex, s, &d);
  invariant();
}
  
  

}
}
}

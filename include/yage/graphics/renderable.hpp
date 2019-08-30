#if !defined(YAGE_GRAPHICS_RENDERABLE)
#  define YAGE_GRAPHICS_RENDERABLE

#include <SDL2/SDL.h>

namespace yage {
namespace graphics {
namespace interface1 {

struct renderable 
{
  virtual void render(const SDL_Rect *) = 0;
};


} // interface1
} // graphics
} // yage

#endif

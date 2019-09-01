#if !defined(YAGE_UTILITY_HPP)
#  define YAGE_UTILITY_HPP
#   include <iostream>
#   include <SDL2/SDL.h>

namespace yage {
namespace utility {
namespace interface1 {


bool intersects(const SDL_Rect& a, const SDL_Rect& b);

}
using namespace interface1;
}
}
#endif


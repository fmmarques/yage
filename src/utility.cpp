#include <yage/utility.hpp>

namespace yage {
namespace utility {

namespace interface1 {

bool intersects(const SDL_Rect& a, const SDL_Rect& b)
{
  std::cout << "a { .x = "<< a.x <<", .y = "<< a.y <<", .w = "<< a.w <<", .h = "<< a.h <<" }\n";
  std::cout << "b { .x = "<< b.x <<", .y = "<< b.y <<", .w = "<< b.w <<", .h = "<< b.h <<" }" << std::endl;
  return 
    ((a.x <= b.x && a.x + a.w >= b.x) && (b.x <= a.x && b.x + b.w >= a.x))
    ||
    ((a.y <= b.y && a.y + a.w >= b.y) && (b.y <= a.y && b.y + b.w >= a.y));
}


}
}
}

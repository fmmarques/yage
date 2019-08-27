#if !defined(YAGE_UTILITY_HPP)
#  define YAGE_UTILITY_HPP
namespace yage {
namespace utility {
namespace interface1 {


constexpr bool intersects(const SDL_Rect& a, const SDL_Rect& b)
{
 return 
  ((a.x <= b.x && a.x + a.w >= b.x) || (b.x <= a.x && b.x + b.w >= a.x))
  &&
  ((a.y <= b.y && a.y + a.w >= b.y) || (b.y <= a.y && b.y + b.w >= a.y));
}

}
using namespace interface1;
}
}
#endif


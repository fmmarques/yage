#if !defined(YAGE_UTILITY_HPP)
#  define YAGE_UTILITY_HPP
#   include <iostream>
#   include <SDL.h>

#	ifndef __FUNCTION_NAME__
#		if (defined(WIN32) || defined(_WIN32) || defined(__WIN32)) && !defined(__CYGWIN__)
#			define __FUNCTION_NAME__   __FUNCDNAME__ 
#		else          //*NIX
#			define __FUNCTION_NAME__   __PRETTY_FUNCTION__  
#		endif
#	endif
#

namespace yage {
namespace utility {
namespace interface1 {


bool intersects(const SDL_Rect& a, const SDL_Rect& b);

}
using namespace interface1;
}
}
#endif


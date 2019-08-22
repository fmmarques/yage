#if !defined(YAGE_GRAPHICS_TEXTURE_HPP)
#  define YAGE_GRAPHICS_TEXTURE_HPP

#include <string>
#include <memory>

#include <SDL2/SDL.h>

namespace yage {
namespace graphics {
namespace interface1 {

class texture 
{
protected:
  void invariant();
public:
  texture(const std::string& name, 
	  std::shared_ptr< SDL_Texture >& resource);
  texture(texture&& other);
  ~texture();

  operator SDL_Texture*();
private:
  std::string name;
  std::shared_ptr< SDL_Texture > resource;
};

}

  using namespace interface1;
}
}

#endif

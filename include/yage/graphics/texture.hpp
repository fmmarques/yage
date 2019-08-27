#if !defined(YAGE_GRAPHICS_TEXTURE_HPP)
#  define YAGE_GRAPHICS_TEXTURE_HPP

#include <string>
#include <memory>


#include <SDL2/SDL.h>

#include <yage/graphics/texture_manager.hpp>

namespace yage {
namespace graphics {
namespace interface1 {

class texture 
{
protected:
  void invariant();
  texture(const std::string& name, std::shared_ptr< SDL_Texture >& resource);


  friend class yage::graphics::texture_manager;
public:
  texture(const texture& other);
  texture(texture&& other);
  texture& operator=(texture&& other);
  texture& operator=(const texture& other);

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

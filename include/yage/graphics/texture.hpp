#if !defined(YAGE_GRAPHICS_TEXTURE_HPP)
#  define YAGE_GRAPHICS_TEXTURE_HPP

#include <string>
#include <memory>


#include <SDL2/SDL.h>

#include <yage/graphics/texture_manager.hpp>

namespace yage {
namespace graphics {
namespace interface1 {

class font;
class texture
{
private:
  int _h;
  int _w;
  std::string _name;
  std::shared_ptr< SDL_Texture > _texture;
protected:
  void invariant() const;
  texture(const std::string& name, std::shared_ptr< SDL_Texture >& resource);

  friend class yage::graphics::font;
  friend class yage::graphics::texture_manager;
public:
  texture(const texture& other);
  texture(texture&& other);
  texture& operator=(texture&& other);
  texture& operator=(const texture& other);

  ~texture();

  operator SDL_Texture*();

  std::string name() const;

  int h() const;
  int w() const;
};

}

  using namespace interface1;
}
}

#endif

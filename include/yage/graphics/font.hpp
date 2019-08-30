#if !defined(YAGE_GRAPHICS_FONT_HPP)
#  define YAGE_GRAPHICS_FONT_HPP

#include <sstream>

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <yage/graphics/texture_manager.hpp>
#include <yage/graphics/font.hpp>


namespace yage {
namespace graphics {
namespace interface1 {

struct __font_deleter_wrapper_t
{
	void operator()(TTF_Font *);
};

class font_manager;
class font
{
private:
  std::string n;
  std::shared_ptr< TTF_Font > f;
  std::unique_ptr< SDL_Texture, __deleter_wrapper_t > t;
  std::stringstream ss;
protected:
 friend class font_manager;
 font(const std::string& name, const std::shared_ptr< TTF_Font >& font);
public:
  font(font&& other);
  font(const font& other);
  ~font();

  font& operator=(font&& other);
  font& operator=(const font& other);

  font& operator<<(const std::string&);


  std::string name() const;
  void name(const std::string& name);


};

}
using namespace interface1;
}
}


#endif

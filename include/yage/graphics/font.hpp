#if !defined(YAGE_GRAPHICS_FONT_HPP)
#  define YAGE_GRAPHICS_FONT_HPP

#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <yage/graphics/texture_manager.hpp>
#include <yage/graphics/texture.hpp>


namespace yage {
namespace graphics {
namespace interface1 {

struct __font_deleter
{
	void operator()(TTF_Font *);
};

class font_manager;
class font
{
private:
  std::string _n;
  int _ppt;
  std::shared_ptr< TTF_Font > _f;
protected:
 friend class font_manager;
 font( const std::string& name,
       int ppt,
       const std::shared_ptr< TTF_Font >& font);
public:
  font(font&& other);
  font(const font& other);
  ~font();

  font& operator=(font&& other);
  font& operator=(const font& other);

  std::string name() const;
  void name(const std::string& name);

  int ppt() const;
  void ppt(int _ppt);

  texture render(const std::string&, const SDL_Color& color );
};

}
using namespace interface1;
}
}


#endif

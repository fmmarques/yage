#if !defined(YAGE_WIDGETS_BUTTON_HPP)
#  define YAGE_WIDGETS_BUTTON_HPP

#include <functional>

#include <SDL.h>

#include <yage/input/input_listener.hpp>
#include <yage/graphics/texture.hpp>
#include <yage/widgets/label.hpp>
#include <yage/graphics/font.hpp>

namespace yage {
namespace widgets {
namespace interface1 {

class button
{
private:
  yage::widgets::label _l;
  std::unique_ptr< SDL_Texture, yage::graphics::__texture_deleter > _b;
  std::function< void() > _c;
  SDL_Color _bg; 
public:
  button( const yage::graphics::font& font, const std::string& text, int ppt, /*const yage::graphics::texture& background,*/ const std::function< void() >& callback, const SDL_Color& background = { 0xC0, 0xC0, 0xC0, 0x00 }, const SDL_Color& foreground = { 0x00, 0x00, 0x00, 0x00 } );
  void on_click();

  void render(const SDL_Rect* r);

  int h() const;
  int w() const;

};

}
using namespace interface1;
}
}

#endif

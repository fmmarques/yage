#include <cassert>
#include <iostream>
#include <yage/graphics/graphics_manager.hpp>
#include <yage/widgets/label.hpp>


namespace yage {
namespace widgets {
namespace interface1 {

label::label( const yage::graphics::font& font,
              const std::string& text,
              int heigth ):
  _f{font}
, _s{text}
, _t{_f.render(_s)}
{}

void label::text(const std::string& text)
{
  _s=text;
  _t = _f.render(_s);
}

std::string label::text() const
{
  return _s;
}

void label::render(const SDL_Rect *rect)
{
  std::string fn { std::string( __PRETTY_FUNCTION__ ) + ": "};
  assert(nullptr != rect);
  assert(rect->h >= _f.ppt());
  auto&& r = yage::graphics::graphics_manager::instance().get_window();
  SDL_RenderCopy(r, _t, NULL, rect );
}

}
}
}


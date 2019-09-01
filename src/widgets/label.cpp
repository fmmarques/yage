#include <cassert>
#include <iostream>
#include <yage/graphics/graphics_manager.hpp>
#include <yage/widgets/label.hpp>


namespace yage {
namespace widgets {
namespace interface1 {

label::label( const yage::graphics::font& font,
              const std::string& text,
              const SDL_Color& color,
              int heigth ):
  _f{font}
, _s{text}
, _t{_f.render(_s, color)}
, _c{.r = color.r, color.g, color.b, color.a }
{}

void label::text(const std::string& text)
{
  _s=text;
  _t = _f.render(_s,_c);
}

std::string label::text() const
{
  return _s;
}

int label::w() const { return _t.w(); }
int label::h() const { return _t.h(); }

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


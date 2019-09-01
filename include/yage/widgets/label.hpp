#if !defined(YAGE_GRAPHICS_LABEL_HPP)
#  define YAGE_GRAPHICS_LABEL_HPP

#  include <yage/graphics/renderable.hpp>
#  include <yage/graphics/texture.hpp>
#  include <yage/graphics/font.hpp>

namespace yage {
namespace widgets {
namespace interface1 {

class label:
  public virtual yage::graphics::renderable
{
protected:
  yage::graphics::font _f;
  std::string _s;
  yage::graphics::texture _t;
  SDL_Color _c;
public:
  label( const yage::graphics::font& font, const std::string& text, const SDL_Color& color, int pixel_height);

  void text(const std::string& text);
  std::string text() const;

  int w() const;
  int h() const;

  void render(const SDL_Rect* r) override;
};

}
using namespace interface1;
}
}

#endif

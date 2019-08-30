#if !defined(YAGE_WIDGETS_LABEL_HPP)
#  define YAGE_WIDGETS_LABEL_HPP

#  include <yage/graphics/font.hpp>

namespace yage {
namespace widgets {
namespace interface1 {

class label
{
protected:
  std::string _text;
  yage::graphics::font _font;
public:
	label( const std::string& text, 
         const yage::graphics::font& font)
	void on_frame()
  {
  }
};


}
using namespace interface1;
}
}

#endif

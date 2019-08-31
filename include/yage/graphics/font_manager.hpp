#if !defined(YAGE_GRAPHICS_FONT_MANAGER_HPP)
#  define YAGE_GRAPHICS_FRONT_MANAGER_HPP

#include <map>

#include <yage/graphics/font.hpp>

namespace yage {
namespace graphics {
namespace interface1 {

class font;
class font_manager
{
private:
  std::map< std::string, std::map< int, std::shared_ptr< TTF_Font > > > fonts_by_name;
  using fonts_by_name_it =  std::map< std::string, std::map< int, std::shared_ptr< TTF_Font > > >::iterator ;
  using font_ref = std::shared_ptr< TTF_Font >;



  font_ref load_font( const std::string& filename,
                      unsigned int ppt );
  font_ref load_ppt( const fonts_by_name_it& it,
                     unsigned int ppt );
protected:
  font_manager();

public:
  static font_manager& instance();
  ~font_manager();

  font load(const std::string& filename, unsigned int ppt);
  void on_release(const yage::graphics::font& font);


};



}
  using namespace interface1;
}
}

#endif

#include <yage/graphics/font_manager.hpp>

namespace yage {
namespace graphics {
namespace interface1 {

font_manager::font_manager():
  fonts_by_name{}
{}

font_manager& font_manager::instance()
{
  static font_manager instance{};
  return instance;
}

font_manager::~font_manager()
{}

font font_manager::load(const std::string& filename, unsigned int ppt)
{
  if (filename.empty())
    throw std::invalid_argument("filename");

  auto fonts_it = fonts_by_name.find(filename);
  if (fonts_it != fonts_by_name.end())
  {
    auto font = fonts_it->second;
    if (font)
      return graphics::font(filename,font);
  }

  auto&& ufont = std::unique_ptr< TTF_Font, __font_deleter_wrapper_t > { 
    TTF_OpenFont(filename.c_str(), ppt) 
  };
  if (nullptr == ufont)
    throw std::runtime_error(SDL_GetError());

  auto&& sfont = std::shared_ptr< TTF_Font >( std::move( ufont ) );
  fonts_by_name.emplace(filename, sfont);

  return graphics::font(filename,sfont);
}

void font_manager::on_release(const yage::graphics::font& font)
{
  auto&& font_ref = fonts_by_name.find(font.name());
  if (font_ref->second.unique())
    fonts_by_name.erase(font_ref);
}


}
using namespace interface1;
}
}

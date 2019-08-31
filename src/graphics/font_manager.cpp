
#include <cassert>
#include <iostream>
#include <yage/graphics/font_manager.hpp>

namespace yage {
namespace graphics {
namespace interface1 {




std::shared_ptr< TTF_Font >
font_manager::load_ppt( const fonts_by_name_it& it,
          unsigned int ppt )
{

  std::string fn { std::string( __PRETTY_FUNCTION__ ) + ": "};
  std::shared_ptr< TTF_Font > sfont {};
  assert(it != fonts_by_name.end());
  auto filename = it->first;
  assert(!filename.empty());
  auto fonts_by_ppt = it->second;
  auto fonts_by_ppt_it = fonts_by_ppt.find(ppt);
  if (fonts_by_ppt_it == fonts_by_ppt.end())
  {

    auto&& ufont = std::unique_ptr< TTF_Font, __font_deleter > ( TTF_OpenFont(filename.c_str(), ppt) );

    if (nullptr == ufont)
    {
      std::cout << fn << "error loading font: \""<< TTF_GetError() <<"\"" << std::endl;
      throw std::runtime_error(TTF_GetError());
    }
    sfont = std::shared_ptr< TTF_Font >( std::move( ufont ) );
    fonts_by_ppt.emplace(ppt, sfont);
  }
  fonts_by_ppt_it = fonts_by_ppt.find(ppt);
  assert(fonts_by_ppt_it != fonts_by_ppt.end());
  return fonts_by_ppt_it->second;
}

std::shared_ptr< TTF_Font >
font_manager::load_font( const std::string& font_name,
           unsigned int ppt )
{
  using ppt_map_t = std::map< int , std::shared_ptr< TTF_Font > >;
  assert(!font_name.empty());
  auto fonts_by_name_it = fonts_by_name.find(font_name);
  if (fonts_by_name.end() == fonts_by_name_it)
    fonts_by_name.emplace( font_name, ppt_map_t{} );
  fonts_by_name_it = fonts_by_name.find(font_name);
  return load_ppt( fonts_by_name_it, ppt );
}


font_manager::font_manager():
  fonts_by_name{}
{

  std::string fn { std::string( __PRETTY_FUNCTION__ ) + ": "};
  if( !TTF_WasInit() && TTF_Init() == -1) 
  {
    std::string err( TTF_GetError());
    std::cout << fn << "error initializing font subsystem: \"" << err << "\"" << std::endl;
    throw std::runtime_error(err);
  }
}

font_manager& font_manager::instance()
{
  static font_manager instance{};
  return instance;
}

font_manager::~font_manager()
{
  std::string fn { std::string( __PRETTY_FUNCTION__ ) + ": "};
  TTF_Quit();

}

font font_manager::load(const std::string& filename, unsigned int ppt)
{
  if (filename.empty())
    throw std::invalid_argument("filename is empty");
  auto&& sfont = load_font(filename, ppt);
  return graphics::font(filename,ppt,sfont);
}

void font_manager::on_release(const yage::graphics::font& font)
{
  auto fonts_by_name_it = fonts_by_name.find(font.name());
  if (fonts_by_name_it == fonts_by_name.end())
    return;

  auto fonts_by_ppt = fonts_by_name_it->second;
  auto fonts_by_ppt_it = fonts_by_ppt.find(font.ppt());

  if (fonts_by_ppt_it == fonts_by_ppt.end())
    return;

  auto&& font_ref = fonts_by_ppt_it;
  if (font_ref->second.unique())
  {
    fonts_by_ppt.erase(fonts_by_ppt_it);
  }
}


}
using namespace interface1;
}
}

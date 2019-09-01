#include <iostream>

#include <yage/graphics/font_manager.hpp>
#include <yage/graphics/texture.hpp>
#include <yage/graphics/graphics_manager.hpp>
#include <yage/graphics/font.hpp> 

namespace yage {
namespace graphics {
namespace interface1 {
	
void __font_deleter::operator()(TTF_Font *font)
{
	std::string fn{ std::string(__PRETTY_FUNCTION__) + std::string(": ") };
	std::cout << fn << "deleting font at " << std::hex << font << std::dec << std::endl;
}

font::font(const std::string& name, int ppt, const std::shared_ptr<TTF_Font>& ptr):
  _n{name}
, _ppt{ppt}
, _f{ptr}
{}

font::font(font&& other):
  _n{other._n}
, _ppt{other._ppt}
, _f{std::move(other._f)}
{}

font::font(const font& other) :
  _n{other._n}
, _ppt{other._ppt}
, _f{ other._f }
{}

font::~font()
{
	yage::graphics::font_manager::instance().on_release(*this);
}

font& font::operator=(font&& other)
{
  _n = other._n;
  _ppt = other._ppt;
  _f = std::move(other._f);
  return *this;
}

font& font::operator=(const font& other)
{
  _n = other._n;
  _ppt = other._ppt;
  _f = std::move(other._f);
  return *this;
}


std::string font::name() const
{
  return _n;
}

void font::name(const std::string& name)
{
  _n = name;
}

int font::ppt() const
{
  return _ppt;
}

void font::ppt(int p)
{
  _ppt = p;
}

texture font::render(const std::string& text, const SDL_Color& color = (SDL_Color){ .r = 0, 0, 0, 0 })
{
  
  std::string fn { std::string( __PRETTY_FUNCTION__ ) + ": "};
//  SDL_Color color { 0, 0, 0};
  std::unique_ptr< SDL_Surface, __surface_deleter > usurface = 
    std::unique_ptr< SDL_Surface, __surface_deleter >( TTF_RenderText_Solid( _f.get(), text.c_str(), color ) );

  if (nullptr == usurface)
    throw std::runtime_error( TTF_GetError() );

  auto&& renderer = yage::graphics::graphics_manager::instance().get_window();
  std::unique_ptr< SDL_Texture, __texture_deleter > utexture = 
    std::unique_ptr< SDL_Texture, __texture_deleter >( SDL_CreateTextureFromSurface( renderer, usurface.get() ) );

  if (nullptr == utexture)
    throw std::runtime_error(SDL_GetError());
  std::shared_ptr< SDL_Texture > stexture = std::move(utexture);
  return texture( _n + ":" + std::to_string(_ppt) + ":" + text, stexture);
}



} // interface
} // graphics
} // yage

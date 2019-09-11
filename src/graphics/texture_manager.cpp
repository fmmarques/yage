#include <cassert>
#include <stdexcept>
#include <string>
#include <memory>
#include <iostream>

#include <SDL.h>

#include <SDL_image.h>

#include <yage/graphics/graphics_manager.hpp>
#include <yage/graphics/texture_manager.hpp>
#include <yage/graphics/texture.hpp>

namespace yage {
namespace graphics {

namespace interface1 { 
// Deleter section

void __texture_deleter::operator()(SDL_Texture *texture)
{
  std::string fn{ std::string(__PRETTY_FUNCTION__) + std::string(": ") };

  if (nullptr != texture)
  {
    std::cout << fn << "destroying texture " << std::hex << texture << std::dec << std::endl; 
    SDL_DestroyTexture(texture);
  }
  // std::cout << fn << "exit" << std::endl;
}

void __surface_deleter::operator()(SDL_Surface *surface)
{
  std::string fn{ std::string(__PRETTY_FUNCTION__) + std::string(": ") };
  //std::cout << fn << "enter" << std::endl;
  if (nullptr != surface)
  {
    std::cout << fn << "destroying surface " << std::hex << surface << std::dec << std::endl; 
    SDL_FreeSurface(surface);
  }
  //std::cout << fn << "exit" << std::endl;
}




// Texture manager
void texture_manager::invariant() const
{
  assert ( 0 != ( (formats && IMG_INIT_JPG) || 
                  (formats && IMG_INIT_PNG) ||  
                  (formats && IMG_INIT_TIF) ) ); 
} 

texture_manager::texture_manager():
  textures_by_name{},
  formats{ IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF }
{
  formats = IMG_Init(formats);
  invariant();
}

texture_manager& texture_manager::instance()
{
  static texture_manager instance;
  return instance;
}

texture_manager::~texture_manager()
{
  IMG_Quit();
  invariant();
}

texture texture_manager::load(const std::string& name)
{
  invariant();

  if (textures_by_name.find(name) != textures_by_name.end())
    return graphics::texture(name, textures_by_name[ name ]);

  std::unique_ptr<SDL_Surface, __surface_deleter> surface(IMG_Load(name.c_str()));
  if (nullptr == surface)
    throw std::runtime_error(SDL_GetError());
  
  std::unique_ptr<SDL_Texture, __texture_deleter> uniq_texture( SDL_CreateTextureFromSurface( graphics_manager::instance().get_renderer(), surface.get() ) );
  if (nullptr == uniq_texture)
    throw std::runtime_error(SDL_GetError());

  std::shared_ptr<SDL_Texture> shared_texture(std::move(uniq_texture));
  textures_by_name.emplace(name, shared_texture);

  invariant();

  return graphics::texture(name,shared_texture);
}

texture texture_manager::load(const std::string& name, uint8_t r, uint8_t g, uint8_t b)
{
  invariant();
  auto&& screen = yage::graphics::graphics_manager::instance().get_window();

  if (textures_by_name.find(name) != textures_by_name.end())
    return graphics::texture(name, textures_by_name[ name ]);

  std::unique_ptr<SDL_Surface, __surface_deleter> surface(IMG_Load(name.c_str()));
  if (nullptr == surface)
    throw std::runtime_error(SDL_GetError());

  SDL_SetColorKey( surface.get(), SDL_TRUE, SDL_MapRGB( surface.get()->format, r, g, b ) );
  
  std::unique_ptr<SDL_Surface, __surface_deleter> blitted_surface(SDL_ConvertSurface(surface.get(), SDL_GetWindowSurface(screen)->format, surface.get()->flags | SDL_SWSURFACE));

  std::unique_ptr<SDL_Texture, __texture_deleter> uniq_texture( SDL_CreateTextureFromSurface( graphics_manager::instance().get_renderer(), surface.get() ) );
  if (nullptr == uniq_texture)
    throw std::runtime_error(SDL_GetError());

  std::shared_ptr<SDL_Texture> shared_texture(std::move(uniq_texture));
  textures_by_name.emplace(name, shared_texture);

  invariant();

  return graphics::texture(name,shared_texture);
}


void texture_manager::on_release(const texture& t)
{
  auto entry = textures_by_name.find(t.name());
  if (entry == std::end(textures_by_name))
    return ;

  auto pointer = entry->second;
  if (pointer.use_count() == 1)
  {
    textures_by_name.erase(t.name());
  } 
}

}
} // graphics
}

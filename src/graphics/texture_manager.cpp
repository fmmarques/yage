#include <cassert>
#include <stdexcept>
#include <string>
#include <memory>

#include <SDL2/SDL.h>

#include <SDL_image.h>

#include <yage/graphics/graphics_manager.hpp>
#include <yage/graphics/texture_manager.hpp>

namespace yage {
namespace graphics {

namespace interface1 { 
// Deleter section

void __deleter_wrapper_t::operator()(SDL_Texture *texture)
{
  if (nullptr != texture)
    SDL_DestroyTexture(texture);
}

void __deleter_wrapper_t::operator()(SDL_Surface *surface)
{
  if (nullptr != surface)
    SDL_FreeSurface(surface);
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

  std::unique_ptr<SDL_Surface, __deleter_wrapper_t> surface(IMG_Load(name.c_str()));
  if (nullptr == surface)
    throw std::runtime_error(SDL_GetError());
  
  std::unique_ptr<SDL_Texture, __deleter_wrapper_t> uniq_texture( SDL_CreateTextureFromSurface( graphics_manager::instance().get_renderer(), surface.get() ) );
  if (nullptr == uniq_texture)
    throw std::runtime_error(SDL_GetError());

  std::shared_ptr<SDL_Texture> shared_texture(std::move(uniq_texture));
  textures_by_name.emplace(name, shared_texture);

  invariant();

  return graphics::texture(name,shared_texture);
}

void texture_manager::on_texture_release(const std::string& name)
{
  auto entry = textures_by_name.find(name);
  if (entry == std::end(textures_by_name))
    throw std::runtime_error(name + " is not a loaded texture.");

  auto pointer = entry->second;
  if (pointer.use_count() == 1)
  {
    textures_by_name.erase(name);
  } 
}

}
} // graphics
}

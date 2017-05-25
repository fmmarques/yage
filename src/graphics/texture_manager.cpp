#include <cassert>
#include <stdexcept>
#include <string>
#include <memory>

#include <SDL2/SDL.h>

#include <SDL_image.h>

#include <graphics/graphics_manager.h>
#include <graphics/texture_manager.h>

namespace graphics {

void __deleter_wrapper_t::operator()(SDL_Texture *pTexture)
{
  if (nullptr != pTexture)
    SDL_DestroyTexture(pTexture);
}

void __deleter_wrapper_t::operator()(SDL_Surface *pSurface)
{
  if (nullptr != pSurface)
    SDL_FreeSurface(pSurface);
}


void texture_manager::invariant() const
{
  assert ( 0 != ( (_iInitiatedFormats && IMG_INIT_JPG) || 
                  (_iInitiatedFormats && IMG_INIT_PNG) ||  
                  (_iInitiatedFormats && IMG_INIT_TIF) ) ); 
} 

texture_manager::texture_manager():
  _mTextureByFilename(),
  _iInitiatedFormats(0)
{
// inicializar o modulo de imagens.
  int iFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
  _iInitiatedFormats = IMG_Init( iFlags );

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

std::shared_ptr<SDL_Texture> texture_manager::load(const std::string& filename)
{
  invariant();

  if (_mTextureByFilename.find(filename) != _mTextureByFilename.end())
    return _mTextureByFilename[ filename ];

  std::unique_ptr<SDL_Surface, __deleter_wrapper_t> upSurface( IMG_Load(filename.c_str() ) );
  if (nullptr == upSurface)
    throw std::runtime_error(SDL_GetError());
  
  std::unique_ptr<SDL_Texture, __deleter_wrapper_t> upTexture( SDL_CreateTextureFromSurface( graphics_manager::instance()->get_renderer(), upSurface.get() ) );
  if (nullptr == upTexture)
    throw std::runtime_error(SDL_GetError());

  std::shared_ptr<SDL_Texture> spTexture(std::move(upTexture));
  _mTextureByFilename.insert(
    std::pair<std::string, std::shared_ptr<SDL_Texture>>( filename, spTexture ));

  invariant();
  return spTexture;
}


} // graphics

#include <string>
#include <memory>
#include <cassert>

#include <yage/graphics/texture.hpp>
#include <yage/graphics/texture_manager.hpp>

namespace yage {
namespace graphics {
namespace interface1 {

// Texture section
void texture::invariant() 
{
  assert( !name.empty() );
  assert( nullptr != resource );
}

texture::texture( const std::string& texture_name,
	          std::shared_ptr< SDL_Texture >& texture_resource ):
  name{texture_name},
  resource{texture_resource}
{
  invariant();
}

texture::~texture()
{
  invariant();
  resource = nullptr;
  texture_manager::instance().on_texture_release(name);
}

texture::operator SDL_Texture*()
{
  invariant();
  return resource.get();
}

	



}
}
}

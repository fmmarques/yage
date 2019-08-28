#include <string>
#include <memory>
#include <cassert>

#include <yage/graphics/texture.hpp>
#include <yage/graphics/texture_manager.hpp>

namespace yage {
namespace graphics {
namespace interface1 {

// Texture section
void texture::invariant() const
{
  assert( !name.empty() );
  assert( nullptr != resource );
}

texture::texture( const std::string& texture_name,
	              std::shared_ptr< SDL_Texture >& texture_resource ):
  name{texture_name}
, resource{texture_resource}
{
  invariant();
}

texture::texture(texture&& other):
  name{other.name}
, resource{other.resource}
{
  invariant();
}

texture::texture(const texture& other):
  name{other.name}
, resource{other.resource}
{
  invariant();
}

texture& texture::operator=(texture&& other)
{
  name = other.name;
  resource = other.resource;
  invariant();
  return *this;
}

texture& texture::operator=(const texture& other)
{
  name = other.name;
  resource = other.resource;
  invariant();
  return *this;
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

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
  assert( !_name.empty() );
  assert( nullptr != _texture );
}

texture::texture( const std::string& texture_name,
	              std::shared_ptr< SDL_Texture >& texture_resource ):
  _h{-1}
, _w{-1}
, _name{texture_name}
, _texture{texture_resource}
{
  SDL_QueryTexture(_texture.get(), NULL, NULL, &_w, &_h );
  invariant();
}

texture::texture(texture&& other):
  _h{-1}
, _w{-1}
,  _name{other._name}
, _texture{other._texture}
{
  invariant();
}

texture::texture(const texture& other):
  _h{-1}
, _w{-1}
, _name{other._name}
, _texture{other._texture}
{
  invariant();
}

texture& texture::operator=(texture&& other)
{
  _h = other._h;
  _w = other._w;
  _name = other._name;
  _texture = other._texture;
  invariant();
  return *this;
}

texture& texture::operator=(const texture& other)
{
  _h = other._h;
  _w = other._w;
  _name = other._name;
  _texture = other._texture;
  invariant();
  return *this;
}

texture::~texture()
{
  invariant();
  _texture = nullptr;
  texture_manager::instance().on_release(*this);
}

texture::operator SDL_Texture*()
{
  invariant();
  return _texture.get();
}

std::string texture::name() const
{
  return _name;
}

int texture::h() const { return _h; };
int texture::w() const { return _w; };



}
}
}

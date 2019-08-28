#if !defined(YAGE_GRAPHICS_SPRITESHEET_HPP)
#  define YAGE_GRAPHICS_SPRITESHEET_HPP

#include <iostream>
#include <map>
#include <vector>

#include <yage/engine/state_machine.hpp>
#include <yage/graphics/texture_manager.hpp>
#include <yage/graphics/texture.hpp>


namespace yage {
namespace graphics {
namespace interface1 {

struct renderable 
{
  virtual void render(const SDL_Rect *) = 0;
};



class animation
{
private:
  texture tex;
  std::vector< SDL_Rect > seq;
  int ticks;
protected:
  void invariant() const {}
public:
  animation(const texture& map);
  void map(uint32_t x, uint32_t y, uint32_t w, uint32_t h); 
  void map_all_of(uint32_t frames, uint32_t x, uint32_t y, uint32_t w, uint32_t h);

  void inline tick()
  {
    //std::string fn {"animation::tick(): "};
    if (seq.size() > 0)
      ticks = (++ticks) % seq.size();
    else
      ticks = 0;
    //std::cout << fn << "enter. tick is " << ticks << ". exit." << std::endl;
  } 

  void render(const SDL_Rect *r);
  void render(int32_t x, int32_t y, int32_t w, int32_t h);
};
  

template< typename id_t, typename key_t >
class sprite:
  public virtual renderable
{
private:
  id_t id;
  texture map;
  std::map< key_t, animation > animations; 

  void invariant() const {}
public:
  sprite(const id_t& id, const texture& map):
    id{id}
  , map{map}
  , animations{}
  {}

  animation& operator[](const key_t& id)
  {
    std::string fname{ "sprite::operator[](const std::key_t&): " };
    //std::cout << fname << "enter" << std::endl;
    //std::cout << fname << "locating animation " << static_cast<int>(id) << " "; 
    auto&& animation_it = animations.begin();
    if (animations.end() != (animation_it = animations.find(id)))
    {
      //std::cout << fname << " exit" << std::endl;
      return animation_it->second;
    }
    //std::cout << "but failed. creating an empty animation." << std::endl;
    animations.emplace( id, map );
    //std::cout << fname << "exit" << std::endl;
    return animations.find(id)->second;
  }


  void render(const SDL_Rect *r) override
  {
//    std::cout << "sprite::render(): enter" << std::endl;
    auto it = animations.begin();
    if (animations.end() != it)
      it->second.render(r);
//    std::cout << "sprite::render(): exit" << std::endl;
  }
};

template< typename sprite_id_t,
          typename animation_id_t = sprite_id_t	>
class spritesheet:
  public virtual renderable
{
private:
  texture map;
  std::map< sprite_id_t, sprite< sprite_id_t, animation_id_t > > sprites;
  void invariant() const {}
public:
  spritesheet(const std::string& name):
    map{ yage::graphics::texture_manager::instance().load(name) },
    sprites{}
  {}

  spritesheet(const std::string& name, uint8_t r, uint8_t g, uint8_t b):
    map{ yage::graphics::texture_manager::instance().load(name,r,g,b) },
    sprites{}
  {}

  spritesheet(spritesheet&& other):
    map(std::move(other.map)),
    sprites(std::move(other.sprites))
  {}

  spritesheet(const spritesheet& other):
    map(other.map),
    sprites(other.sprites)
  {}

  spritesheet& operator=(spritesheet&& other)
  {
    map = std::move(other.map);
    sprites = std::move(other.sprites);
    return *this;
  }

  spritesheet& operator=(const spritesheet& other)
  {
    map = other.map;
    sprites = other.sprites;
    return *this;
  }

  sprite< sprite_id_t, animation_id_t >& operator[](const sprite_id_t& id)
  { 
    std::string fn {"spritesheet::operator[](const sprite_id_t&): "};
    //std::cout << fn << "enter." << std::endl;
    //std::cout << fn << "locating sprite " << static_cast<int>(id) << " ";
    auto sprite_it = sprites.end();
    if (sprites.end() != (sprite_it = sprites.find(id))) 
    {
      //std::cout << "and returning it." << std::endl;
      return sprite_it->second;
    }

    sprites.emplace( std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(id, map));
    sprite_it = sprites.find(id);

    //std::cout << fn << "exit." << std::endl;
    return sprite_it->second;
  }


  void render(const SDL_Rect *r)
  {
    //std::cout << "spritesheet::render(): enter" << std::endl;
    auto it = sprites.begin();
    if (sprites.end() != it)
      it->second.render(r);
    //std::cout << "spritesheet::render(): exit" << std::endl;
  }
};

}
  using namespace interface1;
}
}


#endif

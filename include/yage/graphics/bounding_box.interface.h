#if !defined(GRAPHICS_BOUNDING_BOX_INTERFACE_H)
#  define GRAPHICS_BOUNDING_BOX_INTERFACE_H

#include <SDL2/SDL.h>


namespace graphics {

struct bounding_box_interface
{
  virtual unsigned int x() const = 0;
  virtual unsigned int x(unsigned int x) = 0;

  virtual unsigned int y() const = 0;
  virtual unsigned int y(unsigned int) = 0;

  virtual unsigned int z() const = 0;
  virtual unsigned int z(unsigned int) = 0;

  virtual unsigned int w() const = 0;
  virtual unsigned int w(unsigned int w) = 0;

  virtual unsigned int h() const = 0;
  virtual unsigned int h(unsigned int h) = 0;

  virtual bool intersects(struct bounding_box_interface *) const = 0;
  virtual bool intersects(struct SDL_Rect *) const = 0;

  virtual operator SDL_Rect*() const = 0;
  virtual SDL_Rect get_rectangle() const = 0;

  virtual void draw() const = 0;
};

}

#endif

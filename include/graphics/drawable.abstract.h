#if !defined(GRAPHICS_DRAWABLE_ABSTRACT_H)
#  define GRAPHICS_DRAWABLE_ABSTRACT_H

#include <graphics/bounding_box.interface.h>

namespace graphics {

class drawable_abstract:
  public virtual bounding_box_interface 
{
public:
  drawable_abstract() = default;
  virtual ~drawable_abstract() {};

  virtual unsigned int x() const;
  virtual unsigned int x(unsigned int);

  virtual unsigned int y() const;
  virtual unsigned int y(unsigned int);

  virtual unsigned int z() const;
  virtual unsigned int z(unsigned int);

  virtual unsigned int w() const;
  virtual unsigned int w(unsigned int);

  virtual unsigned int h() const;
  virtual unsigned int h(unsigned int h);

  virtual bool intersects(struct bounding_box_interface *) const;
  virtual bool intersects(struct SDL_Rect *) const;

  virtual operator SDL_Rect*();
  virtual SDL_Rect get_rectangle() const;

  virtual void draw() = 0;

protected:
  unsigned int uiX, uiY;
  unsigned int uiW, uiH;
  SDL_Rect oRectangle;
};

}  // ns graphics

#endif

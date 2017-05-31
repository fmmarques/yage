
#include <yage/graphics/drawable.abstract.h>

namespace graphics {

unsigned int drawable_abstract::x() const 
{
  return uiX;
}

unsigned int drawable_abstract::x(unsigned int x)
{
  uiX = x;
  oRectangle.x = static_cast<int>(x);
  return uiX;
}

unsigned int drawable_abstract::y() const 
{
  return uiY;
}

unsigned int drawable_abstract::y(unsigned int y)
{
  uiY = y;
  oRectangle.y = static_cast<int>(y);
  return uiY;
}

unsigned int drawable_abstract::z() const 
{
  return uiZ;
}

unsigned int drawable_abstract::z(unsigned int z)
{
  uiZ = z;
  return uiZ;
}

unsigned int drawable_abstract::w() const 
{
  return uiW;
}

unsigned int drawable_abstract::w(unsigned int w)
{
  uiW = w;
  oRectangle.w = static_cast<int>(w);
  return uiW;
}

unsigned int drawable_abstract::h() const 
{
  return uiH;
}

unsigned int drawable_abstract::h(unsigned int h)
{
  uiH = h;
  oRectangle.h = static_cast<int>(h);
  return uiH;
}

bool drawable_abstract::intersects(struct bounding_box_interface *pBox) const
{
  bool bOutside = (pBox->x() + pBox->w() < uiX) ||
                  (uiX + uiW < pBox->x()) ||
		  (pBox->y() + pBox->h() < uiY) ||
		  (uiY + uiH < pBox->y());
  return !(bOutside); 
}

bool drawable_abstract::intersects(struct SDL_Rect *pRect) const
{
  bool bOutside = ( pRect->x + pRect->w < oRectangle.x       ) ||
                  ( oRectangle.x  + oRectangle.w  < pRect->x ) ||
		  ( pRect->y + pRect->h < oRectangle.y       ) ||
		  ( oRectangle.y  + oRectangle.h  < pRect->y );
  return !(bOutside); 
}

drawable_abstract::operator SDL_Rect*()
{
  return &oRectangle;
}

SDL_Rect drawable_abstract::get_rectangle() const 
{
  SDL_Rect oResult = oRectangle;
  return oRectangle;
}


}

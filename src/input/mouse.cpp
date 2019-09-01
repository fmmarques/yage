#include <iostream>

#include <yage/input/input_manager.hpp>

#include <yage/input/mouse.hpp>

namespace yage {
namespace input {
namespace interface1 {

mouse::mouse():
  m{}
, r{ .x = 0, 0, 1, 1 }
, e{}
, s{ false, false, false }
{
  input_manager::instance().subscribe(this);
}

mouse& mouse::instance()
{
  static mouse instance{};
  return instance;
}

mouse::~mouse()
{
  input_manager::instance().unsubscribe(this);
}

void mouse::on_mouse_button_up(const SDL_MouseButtonEvent& b)
{
  std::unique_lock<decltype(m)> l(m);
  r.x = b.x;
  r.y = b.y;
  s[CLICK] = s[DOUBLE_CLICK] = s[DRAGGING] = false;
}

void mouse::on_mouse_button_down(const SDL_MouseButtonEvent& e)
{
  std::string fn{ __PRETTY_FUNCTION__ + std::string(": ")};
  std::unique_lock<decltype(m)> l(m);
  r.x = e.x; r.y = e.y;

  s[CLICK] = s[DOUBLE_CLICK] = s[DRAGGING] = false;
  int index = e.clicks % 2;
  s[index] = true;
  std::cout << fn << "received a " << ((index==1)? "click" : "double click") << std::endl;
}

void mouse::on_mouse_movement(const SDL_MouseMotionEvent& e)
{
  std::unique_lock<decltype(m)> l(m);
  std::string fn { std::string( __PRETTY_FUNCTION__ ) + ": "};
  r.x = e.x ; r.y = e.y;
  std::cout << fn << "enter with click: " << std::boolalpha << s[CLICK] << ", double click: " << s[DOUBLE_CLICK] << ", dragging: " << s[DRAGGING] << std::endl;
  if (s[CLICK])
    s[DRAGGING]=true;
  else
    s[CLICK] = s[DOUBLE_CLICK] = s[DRAGGING] = false;
  if (s[DRAGGING])
    std::cout << fn << "mouse is dragging something" << std::endl;
}

bool mouse::hovers(const SDL_Rect& o_r)
{
  std::unique_lock<decltype(m)> l(m);
  return (r.x >= o_r.x && r.x <= o_r.x + o_r.w) &&
         (r.y >= o_r.y && r.y <= o_r.y + o_r.w);
}

bool mouse::is_dragging()
{
  std::unique_lock<decltype(m)> l(m);
  return s[DRAGGING];
}


}
}
}

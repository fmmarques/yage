#if !defined(INPUT_KEYBOARD_LISTENER_INTERFACE_H)
#  define INPUT_KEYBOARD_LISTENER_INTERFACE_H

#include <SDL.h>

namespace yage {
namespace input {
namespace interface1 {

struct keyboard_listener
{
  virtual ~keyboard_listener(){}
  virtual void on_keycode_pressed(const SDL_Keysym& sym) = 0;
  virtual void on_keycode_released(const SDL_Keysym& sym) = 0;  
};

struct mouse_listener
{
  virtual ~mouse_listener() {};
  virtual void on_mouse_button_down(const SDL_MouseButtonEvent& button) = 0;
  virtual void on_mouse_button_up(const SDL_MouseButtonEvent& button) = 0;
  virtual void on_mouse_movement(const SDL_MouseMotionEvent& motion) = 0;
};

struct input_listener:
  public virtual keyboard_listener
, public virtual mouse_listener
{
  virtual ~input_listener(){}
};

}
using namespace interface1;
}
}
#endif

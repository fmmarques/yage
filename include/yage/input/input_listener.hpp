#if !defined(INPUT_KEYBOARD_LISTENER_INTERFACE_H)
#  define INPUT_KEYBOARD_LISTENER_INTERFACE_H

namespace yage {
namespace input {
namespace interface1 {

class input_listener
{
public:
  input_listener();
  virtual ~input_listener();
  virtual void on_keycode_pressed(const SDL_Keysym& sym) = 0;
  virtual void on_keycode_released(const SDL_Keysym& sym) = 0; 
};

}
using interface1::input_listener;
}
}
#endif

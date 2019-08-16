#if !defined(INPUT_KEYBOARD_LISTENER_INTERFACE_H)
#  define INPUT_KEYBOARD_LISTENER_INTERFACE_H

namespace yage {
namespace input {

struct keyboard_listener
{
  virtual void on_key() = 0;
};

}
}
#endif

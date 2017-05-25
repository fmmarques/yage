#if !defined(INPUT_KEYBOARD_LISTENER_INTERFACE_H)
#  define INPUT_KEYBOARD_LISTENER_INTERFACE_H

namespace input {

struct keyboard_listener_interface 
{
  virtual bool operator==( const keyboard_listener_interface& ) const = 0;
  virtual void on_key() = 0;
};

}
#endif

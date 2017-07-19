#if !defined(EVENTS_KEYBOARD_LISTENER_INTERFACE_H)
#  define EVENTS_KEYBOARD_LISTENER_INTERFACE_H

#include <SDL2/SDL.h> 

namespace events {

struct scancode_listener_interface {
  virtual void on_scancode_event(SDL_Event *) = 0;
};

struct keycode_listener_interface {
  virtual void on_keycode_event(SDL_Event *) = 0;
};

struct keyboard_listener_interface:
  public virtual scancode_listener_interface,
  public virtual keycode_listener_interface 
{};

}

#endif

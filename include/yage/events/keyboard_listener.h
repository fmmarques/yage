#if !defined(EVENTS_KEYBOARD_LISTENER_INTERFACE_H)
#  define EVENTS_KEYBOARD_LISTENER_INTERFACE_H

#include <SDL2/SDL.h>

namespace yage {
namespace events {

struct scancode_listener {
  virtual void on_scancode_event(SDL_Event *) = 0;
};

struct keycode_listener {
  virtual void on_keycode_event(SDL_Event *) = 0;
};

struct keyboard_listener:
  public virtual scancode_listener,
  public virtual keycode_listener
{};

}
}

#endif

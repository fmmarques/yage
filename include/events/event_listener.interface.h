#if !defined(EVENTS_EVENT_LISTENER_INTERFACE_H)
#  define EVENTS_EVENT_LISTENER_INTERFACE_H

#include <SDL2/SDL.h> 

namespace events {

struct event_listener_interface {
  virtual void on_event(SDL_Event *) = 0;
};

}
#endif

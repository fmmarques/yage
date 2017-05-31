#if !defined(EVENTS_EVENT_LISTENER_INTERFACE_H)
#  define EVENTS_EVENT_LISTENER_INTERFACE_H

#include <cstdint>

#include <SDL2/SDL.h> 


namespace events {

struct event_listener_interface
{
  virtual void on_event(uint32_t event) = 0;
};

}

#endif

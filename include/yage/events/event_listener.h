#if !defined(YAGE_EVENTS_EVENTLISTENER_H)
#  define YAGE_EVENTS_EVENTLISTENER_H

#include <cstdint>

#include <SDL2/SDL.h>

namespace yage {
namespace events {

struct event_listener
{
  virtual void on_event(const SDL_Event& event) = 0;
};

}
}

#endif

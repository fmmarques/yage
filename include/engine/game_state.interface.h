#if !defined(ENGINE_GAME_STATE_INTERFACE_H)
#  define ENGINE_GAME_STATE_INTERFACE_H

#include <SDL2/SDL.h>

namespace engine {

struct game_state_interface
{
  virtual ~game_state_interface() {}
  

  virtual void on_initialize()   = 0;
  virtual void on_pause()        = 0;
  virtual void on_continue()     = 0;
  virtual void on_deinitialize() = 0;

  virtual void on_event(SDL_Event *) = 0;
  virtual void on_event(SDL_KeyboardEvent *) = 0;
  
  virtual void on_draw() = 0;
};

}
#endif

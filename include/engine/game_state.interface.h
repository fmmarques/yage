#if !defined(ENGINE_GAME_STATE_INTERFACE_H)
#  define ENGINE_GAME_STATE_INTERFACE_H

#include <events/keyboard_listener.interface.h>

namespace engine {

struct game_state_interface:
  public virtual events::scancode_listener_interface
{
  virtual ~game_state_interface() {}
 
  virtual void on_initialize()   = 0;
  virtual void on_pause()        = 0;
  virtual void on_continue()     = 0;
  virtual void on_deinitialize() = 0; 

  virtual void on_render() = 0;
  virtual void on_update() = 0;
};

}
#endif

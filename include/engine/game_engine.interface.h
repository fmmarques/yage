#if !defined(GAME_ENGINE_INTERFACE_H)
#  define GAME_ENGINE_INTERFACE_H

#include <memory>

#include <engine/updatable.interface.h>
#include <engine/game_state.interface.h>

namespace engine {

struct game_engine_interface:
  public virtual engine::updatable_interface 
{
  virtual ~game_engine_interface() {}
  virtual void push( std::unique_ptr<engine::game_state_interface>&& ) = 0;
  virtual std::unique_ptr<engine::game_state_interface>& peek() = 0;
  virtual std::unique_ptr<engine::game_state_interface>& pop() = 0;

}; 

}
#endif

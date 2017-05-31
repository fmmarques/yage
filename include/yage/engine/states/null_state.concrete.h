#if !defined(ENGINE_STATES_NULL_STATE_CONCRETE_H)
#  define ENGINE_STATES_NULL_STATE_CONCRETE_H

#include <stdexcept>
#include <cassert>

#include <yage/engine/game_state.interface.h>
#include <yage/engine/game_state.abstract.h>

namespace engine {
namespace states {

class null_state: 
  public virtual game_state_interface,
  protected virtual game_state_abstract
{
  virtual ~null_state() {};

  null_state():
    game_state_interface(),
    game_state_abstract()
  {}


  void on_render()
  {
    throw std::logic_error("Attempted to render a null state. Null state means a empty state stack which should cause the game engine to stop prior to the rendering.");
  } 

  void on_update()
  {
    assert( "What to do at this point?" && false );
  }
    
};

}
}
#endif

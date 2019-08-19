#if !defined(ENGINE_STATES_NULL_STATE_CONCRETE_H)
#  define ENGINE_STATES_NULL_STATE_CONCRETE_H

#include <stdexcept>
#include <cassert>
#include <iostream>

#include <yage/engine/game_state.hpp>

namespace yage {
namespace engine {
namespace states {

class splash_screen:
  public virtual game_state
{
  virtual ~splash_screen() {};

  splash_screen():
    game_state()
  {}


  void on_render()
  {
    std::clog << "";
  }

  void on_update()
  {
    assert( "What to do at this point?" && false );
  }

};

}
}
}
#endif

#if !defined(GAME_ENGINE_ABSTRACT_H)
#  define GAME_ENGINE_ABSTRACT_H

#include <memory>
#include <queue>

#include <events/event_manager.interface.h>

#include <engine/state_machine.h>

#include <engine/game_state.abstract.h>
#include <engine/runnable.interface.h>
#include <engine/game_engine.interface.h>

namespace engine {

template < typename engine_t,
           typename game_state_t = engine::game_state >
class game_engine:
  public virtual engine::game_engine_interface,
  public virtual engine::runnable_interface,
  
  public virtual engine::machine_state< game_state_t >,
  public virtual engine_t,
  public virtual events::event_manager
{
protected:
  game_engine():
    engine::game_engine_interface(),       // A game engine interface.
    engine::runnable_interface(),          // A threadable interface. Only main thread.
    
    engine::machine_state_interface< game_state_t >(), // A machine state interface
    engine_t(),                            // The engine_t implements game_engine_interface
    events::event_manager(),
  {
    invariant();  
  }


public:
  static std::shared_ptr< game_engine > instance();
  virtual ~game_engine();

// From machine_state_interface< state_t >:
  using engine::machine_state< game_state_t >::push;
  using engine::machine_state< game_state_t >::peek;
  using engine::machine_state< game_state_t >::pop;
/*
  void push( std::unique_ptr< game_state_t >&& rrState );
  std::unique_ptr< engine::game_state_interface >& peek();
  std::unique_ptr< engine::game_state_interface >& pop();
*/
// From runnable_interface:
  virtual void run() = 0;
  virtual void interrupt() = 0;

private:
// Support for game_engine_interface:
//  std::queue< std::unique_ptr< game_state_interface > > _qStates;
// Support for runnable_interface:
  
};

}

#endif

#if !defined(GAME_ENGINE_ABSTRACT_H)
#  define GAME_ENGINE_ABSTRACT_H

#include <memory>
#include <queue>

#include <events/event_manager.interface.h>

#include <engine/runnable.interface.h>
#include <engine/game_engine.interface.h>
#include <engine/game_state.abstract.h>

#include <engine/state_machine.implementation.h>

namespace engine {

template < typename engine_t,
           typename game_state_t = std::unique_ptr< engine::game_state_interface > > 
class game_engine:
  public virtual engine::game_engine_interface,
  public virtual engine::runnable_interface,
  
  public virtual engine::state_machine< game_state_t >,
  public virtual engine_t
{
private:
  void invariant() const { /* TBD */ } 

protected:
  game_engine():
    engine::game_engine_interface(),       // A game engine interface.
    engine::runnable_interface(),          // A threadable interface. Only main thread.
    
    engine::state_machine< game_state_t >(), // A machine state interface
    engine_t()                            // The engine_t implements game_engine_interface
  {
    invariant();  
  }


public:
  template < class _engine_impl_t, class _game_state_t > 
  static engine::game_engine< _engine_impl_t,  _game_state_t >&  instance();
  virtual ~game_engine();
// From machine_state_interface< state_t >:
  using engine::state_machine< game_state_t >::push;
  using engine::state_machine< game_state_t >::peek;
  using engine::state_machine< game_state_t >::pop;
// From runnable_interface:
  virtual void run() = 0;
  virtual void interrupt() = 0;

private:
  
};

}

#endif

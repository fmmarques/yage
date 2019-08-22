#if !defined(YAGE_ENGINE_GAME_ENGINE_ABSTRACT_H)
#  define YAGE_ENGINE_GAME_ENGINE_ABSTRACT_H
#include <iostream>
#include <memory>
#include <queue>
#include <thread>
#include <mutex>

#include <yage/events/event_manager.hpp>

#include <yage/engine/runnable.hpp>
#include <yage/engine/game_state.hpp>

#include <yage/engine/state_machine.hpp>

namespace yage {
namespace engine {

template < typename engine_strategy_t,
           typename game_state_t = yage::engine::game_state >
class game_engine:
  public yage::engine::state_machine< game_state_t >,
  public virtual yage::events::event_listener
{
private:
  void inline invariant() const
  {
    engine::state_machine< game_state_t >::invariant();
  }

protected:
  game_engine():
    engine::state_machine< game_state_t >{}
   ,mutex{}
  {
    std::cout << "game_engine::game_engine(): enter." << std::endl; 
    std::cout << "game_engine::game_engine(): adding game_engine to SDL_QUIT[=" << SDL_QUIT<< "] event listening pool." << std::endl;
    yage::events::event_manager::instance().subscribe(this,SDL_EventType::SDL_QUIT);
    invariant();
    std::cout << "game_engine::game_engine(): exit." << std::endl;
  }


public:
  virtual ~game_engine() 
  {
    invariant();
    yage::events::event_manager::instance().unsubscribe(this,SDL_EventType::SDL_QUIT);
  };
// From machine_state_interface< state_t >:
  using engine::state_machine< game_state_t >::push;
  using engine::state_machine< game_state_t >::peek;
  using engine::state_machine< game_state_t >::pop;
  using engine::state_machine< game_state_t >::length;
// Implementing event_listener:
  virtual void on_event(const SDL_Event& event) override
  {

    std::cout << "yage::game_engine::on_event(): enter" << std::endl;
    switch(event.type)
    {
        case SDL_EventType::SDL_QUIT:
            interrupt();
            break;
        default:
            break;
    }
    std::cout << "yage::game_engine::on_event(): exit" << std::endl;

  }

// From runnable interface:
  void interrupt() 
  {
    std::cout << "yage::game_engine::interrupt(): enter" << std::endl;
    static_cast< engine_strategy_t&>(*this).on_interrupt();
    std::cout << "yage::game_engine::interrupt(): leave" << std::endl;
  }

  void run() 
  {
    std::cout << "yage::game_engine::run(): enter" <<std::endl;
    static_cast< engine_strategy_t &>(*this).on_loop();
    std::cout << "yage::game_engine::run(): leave" <<std::endl;
  }

private:
    std::mutex mutex;
};

}
}

#endif

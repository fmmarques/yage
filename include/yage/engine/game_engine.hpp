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
   ,continue_to_iterate{true}
   ,mutex{}
  {
    yage::events::event_manager::instance().subscribe(this,SDL_EventType::SDL_QUIT);
    invariant();
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
    switch(event.type)
    {
        case SDL_EventType::SDL_QUIT:
            interrupt();
            break;
        default:
            break;
    }
  }

  void run()
  {
    std::string fn(__FUNCTION_NAME__);

    bool do_next_iteration = true;

    {
      std::unique_lock< decltype(mutex) > lock(mutex);
      do_next_iteration = continue_to_iterate;
    }

    auto&& event_mgr = yage::events::event_manager::instance();
    while (do_next_iteration)
    {
  
      do_next_iteration &= static_cast< engine_strategy_t &>(*this).on_loop();
      {
        std::unique_lock< decltype(mutex) > lock(mutex);
        do_next_iteration &= continue_to_iterate;
      }
      event_mgr.poll_event();
    }

    std::cout << fn << "engine's main loop exited. joining event_manager's thread." << std::endl;
    yage::events::event_manager::instance().interrupt();
  }

  void interrupt()
  {
    std::string fn( std::string(__FUNCTION_NAME__) + std::string(": ") );
    std::cout << fn << "interrupting the engine's main loop." << std::endl;
    std::unique_lock< decltype(mutex) > lock( mutex );
    continue_to_iterate = false;
    static_cast< engine_strategy_t & >( *this ).on_interrupt();
  } 

private:
    std::mutex mutex;
    volatile bool continue_to_iterate;
};

}
}

#endif

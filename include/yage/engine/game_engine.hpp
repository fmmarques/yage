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
    //std::cout << "game_engine::game_engine(): enter." << std::endl; 
    //std::cout << "game_engine::game_engine(): adding game_engine to SDL_QUIT[=" << SDL_QUIT<< "] event listening pool." << std::endl;
    yage::events::event_manager::instance().subscribe(this,SDL_EventType::SDL_QUIT);
    invariant();
    //std::cout << "game_engine::game_engine(): exit." << std::endl;
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

   // std::cout << "yage::game_engine::on_event(): enter" << std::endl;
    switch(event.type)
    {
        case SDL_EventType::SDL_QUIT:
            interrupt();
            break;
        default:
            break;
    }
    //std::cout << "yage::game_engine::on_event(): exit" << std::endl;

  }

  void run() 
  {
    std::string fn(__PRETTY_FUNCTION__);
    //std::cout << fn << "enter" << std::endl;

    bool do_next_iteration = true;

    {
      std::unique_lock< decltype(mutex) > lock(mutex);
      do_next_iteration = continue_to_iterate;
    }

    while (do_next_iteration)
    {
  
      do_next_iteration &= static_cast< engine_strategy_t &>(*this).on_loop();
      {
        std::unique_lock< decltype(mutex) > lock(mutex);
        do_next_iteration &= continue_to_iterate;
      }
      //std::cout << fn << "do_next_iteration: " << do_next_iteration << std::endl;    
    }

    std::cout << fn << "joining event_manager's thread." << std::endl;
    yage::events::event_manager::instance().interrupt();
    //std::cout << fn << "leave" <<std::endl;
  }

  void interrupt()
  {
    std::string fn( std::string(__PRETTY_FUNCTION__) + std::string(": :w
		") );
    std::cout << fn << "interrupting the main loop";
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

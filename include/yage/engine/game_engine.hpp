#if !defined(YAGE_ENGINE_GAME_ENGINE_ABSTRACT_H)
#  define YAGE_ENGINE_GAME_ENGINE_ABSTRACT_H

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
  public virtual yage::engine::runnable,
  public virtual yage::engine::state_machine< game_state_t >,
  public virtual yage::events::event_listener,
  public virtual engine_strategy_t
{
private:
  void invariant() const
  {
	engine_strategy_t::invariant();
	engine::state_machine< game_state_t >::invariant();
  }

protected:
  game_engine():
    engine_strategy_t{},
    engine::state_machine< game_state_t >{},
    thread(&game_engine::run, this),
    mutex{},
    continue_thread_execution{true}
  {
    std::unique_lock<std::mutex> lock{ mutex, std::defer_lock };
    lock.lock();
    invariant();
  }


public:
  template < class _engine_impl_t, class _game_state_t >
  static engine::game_engine< _engine_impl_t,  _game_state_t >&  instance()
  {
    static engine::game_engine< _engine_impl_t, _game_state_t > instance;
    return instance;
  }

  virtual ~game_engine();
// From machine_state_interface< state_t >:
  using engine::state_machine< game_state_t >::push;
  using engine::state_machine< game_state_t >::peek;
  using engine::state_machine< game_state_t >::pop;
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

// From runnable_interface:

  virtual void interrupt() override
  {
    std::unique_lock<std::mutex> lock{ mutex, std::defer_lock };
    lock.lock();
    continue_thread_execution = false;
  }

  virtual void run() override
  {
    events::event_manager& event_mgr = yage::events::event_manager::instance();
    event_mgr.subscribe(this,SDL_EventType::SDL_QUIT);
 }


private:
    std::thread thread;
    std::mutex mutex;
    bool continue_thread_execution;
};

}
}

#endif

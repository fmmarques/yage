#include <mutex>
#include <memory>
#include <cassert>
#include <stdexcept>

#include <yage/input/input_manager.hpp>
#include <yage/events/event_manager.hpp>

namespace yage {
namespace input {

void input_manager::invariant()
{}

input_manager::input_manager():
    mutex{},
    input_listeners{}
{
  using yage::events::event_manager;

  std::lock_guard<decltype(mutex)> lock(mutex);
  invariant();
  event_manager::instance().subscribe(this, { ::SDL_KEYDOWN });
}

input_manager& input_manager::instance()
{
  static yage::input::input_manager instance{};
  return instance;
}

input_manager::~input_manager()
{
  invariant();
}

void input_manager::subscribe( input_listener *listener )
{
  std::lock_guard<decltype(mutex)> lock(mutex);
  invariant();
  input_listeners.push_back( listener );
  invariant();
}

void input_manager::unsubscribe( input_listener *listener )
{
  std::lock_guard<decltype(mutex)> lock(mutex );
  invariant();
  input_listeners.remove( listener );
  invariant();
}
// event_listener implementation
void input_manager::on_event(const SDL_Event& ev) 
{
  std::list< input_listener * > listeners;
    
  {
    std::lock_guard<decltype(mutex)> lock(mutex);
    invariant(); 
    listeners = input_listeners;
    invariant();
  }

  for (auto&& listener : listeners)
  {
    switch(ev.type)
    {
      case SDL_KEYDOWN:
        listener->on_keycode_pressed(ev.key.keysym);
	break;
      case SDL_KEYUP:
	listener->on_keycode_released(ev.key.keysym);
	break;
      default:
	// Only SDL_QUIT, SDL_APPTERMINATING, and SDL_* input related events should ever reach here.
	break;

    }  
  }
}

} // input
} // yage

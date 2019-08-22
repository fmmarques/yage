#include <iostream>
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
  event_manager::instance().subscribe(
    this, 
    {  ::SDL_KEYDOWN  		,::SDL_KEYUP 
      ,::SDL_MOUSEBUTTONDOWN 	,::SDL_MOUSEBUTTONUP });
}

input_manager& input_manager::instance()
{
  static yage::input::input_manager instance{};
  return instance;
}

input_manager::~input_manager()
{
  invariant();
  yage::events::event_manager::instance().unsubscribe(
    this,
    {  ::SDL_KEYDOWN  		,::SDL_KEYUP 
      ,::SDL_MOUSEBUTTONDOWN 	,::SDL_MOUSEBUTTONUP });

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
      case SDL_MOUSEBUTTONDOWN:
	std::cout << "input_manager::on_event(const SDL_Event&): " <<ev.button.x<< std::endl;
	listener->on_mouse_button_down(ev.button);
	break;
      case SDL_MOUSEBUTTONUP:
	listener->on_mouse_button_up(ev.button);
	break;
      case SDL_MOUSEMOTION:
	listener->on_mouse_movement(ev.motion);
	break;
      default:
	std::cout << "input_manager::on_event(const SDL_Event&): received event " << ev.type << " and will not pass it" << std::endl;
	break;

    }  
  }
}

} // input
} // yage

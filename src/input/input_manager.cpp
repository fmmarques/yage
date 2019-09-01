#include <iostream>
#include <mutex>
#include <memory>
#include <cassert>
#include <stdexcept>


#include <yage/input/input_manager.hpp>
#include <yage/events/event_manager.hpp>

namespace yage {
namespace input {

namespace interface1 {



void input_manager::invariant()
{}

input_manager::input_manager():
  mutex{}
, mouse_listeners{}
, keyboard_listeners{}
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
  subscribe((keyboard_listener *)listener);
  subscribe((mouse_listener *)listener);
}


void input_manager::subscribe( keyboard_listener *listener )
{
  std::lock_guard<decltype(mutex)> lock(mutex );
  invariant();
  keyboard_listeners.insert(keyboard_listeners.end(), listener );
  invariant();
}

void input_manager::subscribe( mouse_listener *listener )
{
  std::lock_guard<decltype(mutex)> lock(mutex );
  invariant();
  mouse_listeners.insert(mouse_listeners.end(), listener );
  invariant();
}

void input_manager::unsubscribe( mouse_listener *listener )
{
  std::lock_guard<decltype(mutex)> lock(mutex );
  invariant();
  mouse_listeners.remove( listener );
  invariant();
}

void input_manager::unsubscribe( keyboard_listener *listener )
{
  std::lock_guard<decltype(mutex)> lock(mutex );
  invariant();
  keyboard_listeners.remove( listener );
  invariant();
}

void input_manager::unsubscribe( input_listener *listener )
{
  unsubscribe((mouse_listener*)listener);
  unsubscribe((keyboard_listener*)listener);

}
// event_listener implementation
void input_manager::on_event(const SDL_Event& ev) 
{
  std::list< mouse_listener * > m_l;
  std::list< keyboard_listener * > k_l;
    
  {
    std::lock_guard<decltype(mutex)> lock(mutex);
    invariant(); 
    m_l = mouse_listeners;
    k_l = keyboard_listeners;
    invariant();
  }

  switch(ev.type)
  {
    case SDL_KEYDOWN:
      for(auto&& l : k_l) 
        l->on_keycode_pressed(ev.key.keysym);
      break;
    case SDL_KEYUP:
      for(auto&& l : k_l) 
        l->on_keycode_released(ev.key.keysym);
      break;
    case SDL_MOUSEBUTTONDOWN:
      for(auto&& l : m_l) 
        l->on_mouse_button_down(ev.button);
      break;
    case SDL_MOUSEBUTTONUP:
      for(auto&& l : m_l) 
        l->on_mouse_button_up(ev.button);
      break;
    case SDL_MOUSEMOTION:
      for(auto&& l : m_l) 
        l->on_mouse_movement(ev.motion);
      break;
    default:
      std::cout << "input_manager::on_event(const SDL_Event&): received event " << ev.type << " and will not pass it" << std::endl;
	break;

  }
}


} // interface
} // input
} // yage

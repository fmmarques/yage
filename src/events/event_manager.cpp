
#include <cassert>
#include <stdexcept>

#include <iostream>
#include <list>
#include <memory>
#include <shared_mutex>
#include <mutex>
#include <algorithm>
#include <thread>


#include <SDL2/SDL.h>

#include <yage/events/event_listener.hpp>
#include <yage/events/event_manager.hpp>

namespace yage {
namespace events {

void event_manager::invariant()
{

}

event_manager::event_manager():
  mutex{}
  ,event_listeners{}
  ,continue_thread_execution{true}
  ,th(&event_manager::run,this)
{
  std::lock_guard<std::shared_mutex> lock(mutex);
  invariant();
}

event_manager::~event_manager()
{
}


event_manager& event_manager::instance()
{
  static events::event_manager instance;
  return instance;
}

// Listeners
void event_manager::subscribe(
  events::event_listener * listener,
  SDL_EventType event )
{
  std::string fn{ std::string( __PRETTY_FUNCTION__ ) + std::string(": ") }
  std::unique_lock<decltype(mutex)> lock(mutex, std::defer_lock);

  //std::cout << fn << "enter. " << std::endl;
  
  lock.lock();
  invariant();

  auto&& listeners = event_listeners[ event ];
  listeners.push_back(listener);

  invariant();
  lock.unlock();


  //std::cout << fn << "exit. " << std::endl;
}

void event_manager::subscribe(
  events::event_listener *listener,
  std::vector< SDL_EventType >&& events )
{
	std::string fn{ std::string(__PRETTY_FUNCTION__) + std::string(": ") }
	std::cout << fn;
//	std::cout << "enter. ";
	std::unique_lock< decltype(mutex) > lock(mutex, std::defer_lock);
  
  auto event_iterator = std::cbegin(events);
  while (event_iterator != std::cend(events))
  {
    std::cout << "adding listener to " << *event_iterator << " event. ";
    lock.lock();
    invariant();
    
    auto&& listeners = event_listeners[ *event_iterator ];
    listeners.push_back(listener);

    invariant();
    lock.unlock();
    event_iterator++;
  }
//  std::cout << "exit. " << std::endl;
  std::cout << std::endl;
}

void event_manager::unsubscribe(
  events::event_listener * listener,
  SDL_EventType event )
{
  std::unique_lock<decltype(mutex)> lock(mutex, std::defer_lock);

  lock.lock();
  invariant();

  auto&& listeners = event_listeners[ event ];
  listeners.remove( listener );

  invariant();
  lock.unlock();

}

void event_manager::unsubscribe(
  events::event_listener * listener,
  std::vector< SDL_EventType >&& events )
{
  std::unique_lock<decltype(mutex)> lock(mutex, std::defer_lock);

  auto event_iterator = std::cbegin(events);
  while (event_iterator != std::cend(events))
  {
    
    lock.lock();
    invariant();
    
    auto&& listeners = event_listeners[ *event_iterator ];
    listeners.push_back(listener);
    
    invariant();
    
    lock.unlock();
    event_iterator++;
  }


}

void event_manager::emit(const SDL_Event& event)
{
    std::cout << "event_manager::emit(const SDL_Event&): enter. ";
    std::shared_lock<decltype(mutex)> lock(mutex,std::defer_lock);

    SDL_EventType event_type = static_cast< SDL_EventType>(event.type);
    lock.lock();
    std::list< event_listener * > listeners = event_listeners[ event_type ];
    lock.unlock();
    std::cout << " Emiting event [event.type = " << event.type << "] to " << listeners.size() << " listeners." << std::endl;

    std::for_each(
        listeners.begin(),
        listeners.end(),
        [&event] (event_listener * listener) {
            listener->on_event(event);
        });
    std::cout << "event_manager::emit(const SDL_Event&): exit." << std::endl;
}

// Runnable

void yage::events::event_manager::interrupt()
{
  std::cout << "event_manager::interrupt(): attempting to join this_thread("<< std::this_thread::get_id() <<") with event_manager's thread("<< th.get_id()<<")"<< std::endl;
  th.join();
}

void event_manager::run()
{
    std::cout << "event_manager::run(): enter " << std::endl;
    SDL_Event curr_event {};
    std::shared_lock<decltype(mutex)> lock(mutex,std::defer_lock);
    bool continue_next_iteration = false;

    lock.lock();
    continue_next_iteration = continue_thread_execution;
    lock.unlock();

    while (continue_next_iteration && SDL_WaitEvent(&curr_event))
    {
        switch (curr_event.type)
        {
        case SDL_QUIT:
            emit(curr_event);
            continue_next_iteration = false;
            break;
	default:
	    emit(curr_event);
        }


        lock.lock();
        continue_next_iteration = continue_thread_execution && continue_next_iteration;
        lock.unlock();
    }
    std::cout << "event_manager::run(): exit" << std::endl;
}

}
}

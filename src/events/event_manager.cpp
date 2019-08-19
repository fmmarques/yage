#include <cassert>
#include <stdexcept>

#include <list>
#include <memory>
#include <shared_mutex>
#include <mutex>
#include <algorithm>


#include <SDL2/SDL.h>

#include <yage/events/event_listener.hpp>
#include <yage/events/event_manager.hpp>

namespace yage {
namespace events {

void event_manager::invariant()
{

}

event_manager::event_manager():
  mutex{},
  event_listeners{},
  continue_thread_execution{true}
{
  std::lock_guard<std::shared_mutex> lock(mutex);
  invariant();
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
  std::unique_lock<decltype(mutex)> lock(mutex, std::defer_lock);

  lock.lock();
  invariant();

  auto listeners = event_listeners[ event ];
  listeners.push_back(listener);

  invariant();
  lock.unlock();
}

void event_manager::subscribe(
  events::event_listener *listener,
  std::vector< SDL_EventType >&& events )
{
  std::unique_lock< decltype(mutex) > lock(mutex, std::defer_lock);

  auto event_iterator = std::cbegin(events);
  while (event_iterator != std::cend(events))
  {
    lock.lock();
    invariant();
    auto listeners = event_listeners[ *event_iterator ];
    listeners.push_back(listener);
    invariant();
    lock.unlock();
    std::next(event_iterator);
  }
}

void event_manager::unsubscribe(
  events::event_listener * listener,
  SDL_EventType event )
{
  std::unique_lock<decltype(mutex)> lock(mutex, std::defer_lock);

  lock.lock();
  invariant();

  auto listeners = event_listeners[ event ];
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
    auto listeners = event_listeners[ *event_iterator ];
    listeners.push_back(listener);
    invariant();
    lock.unlock();
    std::next(event_iterator);
  }

  invariant();
  lock.unlock();

}

void event_manager::emit(const SDL_Event& event)
{
    std::shared_lock<decltype(mutex)> lock(mutex,std::defer_lock);

    SDL_EventType event_type = static_cast< SDL_EventType>(event.type);
    lock.lock();
    std::list< event_listener * >& listeners = event_listeners[ event_type ];


    std::for_each(
        listeners.begin(),
        listeners.end(),
        [&event] (event_listener * listener) {
            listener->on_event(event);
        });
    lock.unlock();
}

// Runnable

void yage::events::event_manager::interrupt()
{

}

void event_manager::run()
{
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
            continue_thread_execution = false;
            break;
        }


        lock.lock();
        continue_next_iteration = continue_thread_execution;
        lock.unlock();
    }
}

}
}

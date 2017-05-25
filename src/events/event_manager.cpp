#include <cassert>
#include <stdexcept>

#include <list>
#include <memory>
#include <mutex>

#include <SDL2/SDL.h>

#include <events/event_listener.interface.h>
#include <events/event_manager.h>

events::event_manager::event_manager():
  _mMutex(),
  _mListeners()
{
  invariant();
}

void events::event_manager::invariant()
{

}

events::event_manager& events::event_manager::instance()
{
  static events::event_manager instance;
  return instance;
}

void events::event_manager::register_listener( 
  std::shared_ptr< events::event_listener_interface >& spListener,
  uint32_t event )
{
  std::unique_lock<std::mutex> lLock(_mMutex, std::defer_lock);

  lLock.lock();
  invariant();

  auto lListeners = _mListeners[ event ];
  lListeners.push_back( spListener );

  invariant();
  lLock.unlock();
}

void events::event_manager::unregister_listener( 
  std::shared_ptr< events::event_listener_interface >& spListener,
  uint32_t event )
{
  std::unique_lock<std::mutex> lLock(_mMutex, std::defer_lock);

  lLock.lock();
  invariant();

  auto lListeners = _mListeners[ event ];
  lListeners.remove( spListener );

  invariant();
  lLock.unlock();

}



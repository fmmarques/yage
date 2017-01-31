#include <mutex>
#include <memory>
#include <cassert>
#include <stdexcept>

#include <input/input_manager.h>

void input::input_manager::invariant()
{}

input::input_manager::input_manager()
{
  invariant();
}

std::weak_ptr<input::input_manager> input::input_manager::instance()
{
  static std::shared_ptr<input::input_manager> spInstance = std::make_shared<input::input_manager>();
  return spInstance;
}

input::input_manager::~input_manager()
{
  invariant();
}

void input::input_manager::register_listener( std::shared_ptr<keyboard_listener_interface>& spListener )
{
  std::lock_guard<std::mutex> lLock(_mMutex);
  invariant();
  _lListeners.push_back( spListener );
  invariant();
}

void input::input_manager::unregister_listener( shared_ptr<keyboard_listener_interface>& spListener )
{
  std::lock_guard<std::mutex> lLock(_mMutex );
  invariant();
  _lListeners.remove( spListener );
  invariant();
}

void input::input_manager::run()
{
  std::lock_guard<std::mutex> lLock(_mMutex, std::defer_lock);
  invariant();
//  for ( shared_ptr<input_event_listener>
  invariant();
}

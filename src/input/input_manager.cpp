#include <mutex>
#include <memory>
#include <cassert>
#include <stdexcept>

#include <yage/input/input_manager.h>

void input::input_manager::invariant()
{}

input::input_manager::input_manager()
{
  invariant();
}

input::input_manager& input::input_manager::instance()
{
  static input::input_manager spInstance;
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

void input::input_manager::unregister_listener( std::shared_ptr<keyboard_listener_interface>& spListener )
{
  std::lock_guard<std::mutex> lLock(_mMutex );
  invariant();
  _lListeners.remove( spListener );
  invariant();
}



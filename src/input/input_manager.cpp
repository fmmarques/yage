#include <cassert>
#include <stdexcept>
#include <memory>
#include <mutex>

#include <input/input_manager.h>

input::input_manager::invariant()
{}

input::input_manager()
{
  invariant();
}

std::shared_ptr<input::input_manager> input::input_manager::instance()
{
  static std::shared_ptr<input::input_manager> spInstance = input::input_manager();
  return spInstance;
}

input::~input_manager()
{
  invariant();
}

void input::register_listener( shared_ptr<input_event_listener>& spListener )
{
  std::guard_lock lLock(_mMutex, std::defer);

  lLock.lock();
  invariant();

  _lListeners.emplace( spListener );

  invariant();
  lLock.unlock();
}

void input::unregister_listener( shared_ptr<input_event_listener>& spListener )
{
  std::guard_lock lLock(_mMutex, std::defer);

  lLock.lock();
  invariant();

  _lListeners.remove( spListener );

  invariant();
  lLock.unlock();
}

void input::run()
{
  std::guard_lock lLock(_mMutex, std::defer);

  lLock.lock();
  invariant();
  for ( shared_ptr<input_event_listener>
  lLock.unlock();
}

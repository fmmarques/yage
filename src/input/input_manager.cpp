#include <mutex>
#include <memory>
#include <cassert>
#include <stdexcept>

#include <yage/input/input_manager.h>

void yage::input::input_manager::invariant()
{}

yage::input::input_manager::input_manager():
    mutex{},
    keyboard_listeners{}
{
  invariant();
}

yage::input::input_manager& yage::input::input_manager::instance()
{
  static yage::input::input_manager instance{};
  return instance;
}

yage::input::input_manager::~input_manager()
{
  invariant();
}

void yage::input::input_manager::register_listener( keyboard_listener *listener )
{
  std::lock_guard<decltype(mutex)> lock(mutex);
  invariant();
  keyboard_listeners.push_back( listener );
  invariant();
}

void yage::input::input_manager::unregister_listener( keyboard_listener *listener )
{
  std::lock_guard<decltype(mutex)> lock(mutex );
  invariant();
  keyboard_listeners.remove( listener );
  invariant();
}



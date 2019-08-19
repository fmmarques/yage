#include <yage/input/input_listener.hpp>
#include <yage/input/input_manager.hpp>

namespace yage {
namespace input {

namespace interface1 {

input_listener::input_listener() 
{
  auto input_manager = yage::input::input_manager::instance();
  input_manager.subscribe(this);  
}

input_listener::~input_listener()
{
  auto input_manager = yage::input::input_manager::instance();
  input_manager.unsubscribe(this);
}

}
}
}

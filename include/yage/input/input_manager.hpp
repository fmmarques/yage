#if !defined(INPUT_INPUT_MANAGER_H)
#define INPUT_INPUT_MANAGER_H


#include <memory>
#include <list>
#include <shared_mutex>

#include <yage/engine/runnable.hpp>
#include <yage/events/event_listener.hpp>
#include <yage/input/input_listener.hpp>

namespace yage {
namespace input {
namespace interface1 {

class input_manager:
  public virtual yage::events::event_listener
{
protected:
  void invariant();
  input_manager();
public:
  static input_manager& instance();
  virtual ~input_manager();

// 
  void subscribe( input_listener *listener );
  void subscribe( mouse_listener *listener );
  void subscribe( keyboard_listener *listener );
  
  void unsubscribe( keyboard_listener *listener );
  void unsubscribe( mouse_listener *listener );
  void unsubscribe( input_listener *listener );
// event_listener implementation
  void on_event(const SDL_Event& event) override; 
//

private:
  std::shared_mutex mutex;
  std::list< mouse_listener *> mouse_listeners;
  std::list< keyboard_listener *> keyboard_listeners;

};

}
  using namespace interface1;
}
}
#endif

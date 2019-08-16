#if !defined(INPUT_INPUT_MANAGER_H)
#define INPUT_INPUT_MANAGER_H


#include <memory>
#include <list>
#include <shared_mutex>

#include <yage/input/keyboard_listener.h>

namespace yage {
namespace input {

class input_manager
{
protected:
  void invariant();
  input_manager();
public:
  static input_manager& instance();
  virtual ~input_manager();

  void register_listener( keyboard_listener *listener );
  void unregister_listener( keyboard_listener *listener );
private:
  std::shared_mutex mutex;
  std::list< keyboard_listener *> keyboard_listeners;
};

}
}
#endif

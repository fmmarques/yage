#if !defined(INPUT_INPUT_MANAGER_H)
#define INPUT_INPUT_MANAGER_H

#include <memory>
#include <list>

#include <input/keyboard_listener.interface.h>

namespace input {

class input_manager
{
protected:
  void invariant();
  input_manager();
public:
  input_manager& instance();
  ~input_manager();

  void register_listener( std::shared_ptr<keyboard_listener_interface>& spListener );
  void unregister_listener( std::shared_ptr<keyboard_listener_interface>& spListener );
  void run();
private:
  std::mutex _mMutex;
  std::list< std::shared_ptr<keyboard_listener_interface> > _lListeners;
};

}
#endif

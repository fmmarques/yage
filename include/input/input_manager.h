#if !defined(INPUT_INPUT_MANAGER_H)
#define INPUT_INPUT_MANAGER_H

#include <memory>

#include <input/keyboard_listener_interface.h>

namespace input {

class input_manager:
{
protected:
  void invariant();
  input_manager();
public:
  std::shared_ptr<input_manager> instance();
  ~input_manager();

  void register_listener( std::shared_ptr<keyboard_listener_interface>& spListener );

  
  void unregister_listener( std::shared_ptr<keyboard_listener_listener>& spListener );

  void run();
private:
  static std::shared_ptr<input_manager> pInstance;
  std::mutex _mMutex;
  std::list<keyboard_listener_interface> _lListeners;
};

}
#endif

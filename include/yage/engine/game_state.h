#if !defined(GAME_ENGINE_ABSTRACT_H)
#  define GAME_ENGINE_ABSTRACT_H

#include <yage/events/keyboard_listener.h>
#include <yage/engine/game_state.h>

namespace yage {
namespace engine {

enum class game_state_status {
  UNINITIALIZED,
  INITIALIZED,
  PAUSED,
  CONTINUING,
  DEINITIALIZING
};

class game_state:
  public virtual events::scancode_listener
{
public:
  game_state();
  ~game_state();

  virtual void on_initialize();
  virtual void on_pause();
  virtual void on_continue();
  virtual void on_deinitialize();
  virtual void on_render() = 0;
  virtual void on_update() = 0;

protected:
  virtual const game_state_status& get_status() const;
  virtual void set_status(game_state_status&& status);

private:
  game_state_status _eStatus;

};

}
}

#endif

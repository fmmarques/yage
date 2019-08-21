#if !defined(ENGINE_GAME_STATE_HPP)
#  define ENGINE_GAME_STATE_HPP


#include <yage/engine/runnable.hpp>

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
	public virtual yage::engine::runnable
{
public:
  game_state();
  virtual ~game_state();

  virtual void on_initialize();
  virtual void on_pause();
  virtual void on_continue();
  virtual void on_deinitialize();

public:
  virtual void run() = 0;
  virtual void interrupt() = 0;

protected:
  virtual const game_state_status& get_status() const;
  virtual void set_status(game_state_status&& status);

private:
  game_state_status status;

};

}
}

#endif

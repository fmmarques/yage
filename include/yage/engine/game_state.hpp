#if !defined(ENGINE_GAME_STATE_HPP)
#  define ENGINE_GAME_STATE_HPP


#include <yage/engine/runnable.hpp>

namespace yage {
namespace engine {
namespace interface1 {

enum class game_state_status {
  UNINITIALIZED,
  INITIALIZED,
  PAUSED,
  CONTINUING,
  DEINITIALIZING
};

template < typename strategy_t >
class game_state:
  public virtual yage::engine::runnable
{
public:
  game_state():
    status( engine::interface1::game_state_status::UNINITIALIZED )
  {}

  virtual ~game_state();

  virtual void on_initialize() 
  {
    static_cast< strategy_t * >(this)->on_initialize();
    set_status( game_state_status::INITIALIZED );
  }
  
  virtual void on_pause()
  {
    static_cast< strategy_t * >(this)->on_pause();
    set_status( game_state_status::PAUSED );
  }

  virtual void on_continue()
  {
    static_cast< strategy_t *>(this)->on_continue();
    set_status( game_state_status::CONTINUING );
  }

  virtual void on_deinitialize()
  {
    static_cast< strategy_t *>(this)->on_deinitialize();
    set_status( game_state_status::DEINITIALIZING );
  } 

public:
  virtual void run() 
  {
    static_cast< strategy_t *>(this)->run();
  }

  virtual void interrupt() 
  {
    static_cast< strategy_t *>(this)->interrupt();
  }

protected:
  virtual const game_state_status& get_status() const 
  {
    return status;
  }
  
  virtual void set_status(game_state_status&& status) 
  { 
    this->status = status;
  }
private:
  game_state_status status;

};

}
using namespace interface1;
}
}

#endif

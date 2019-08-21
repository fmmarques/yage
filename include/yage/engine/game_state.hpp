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

class game_state: 
  public virtual yage::engine::runnable
{
public:
  virtual void on_initialize() = 0;
  virtual void on_pause() = 0;
  virtual void on_continue() = 0;
  virtual void on_deinitialize() = 0;
};

template < typename strategy_t >
class game_state_impl:
  public virtual game_state
{
public:
  game_state_impl():
    status( engine::interface1::game_state_status::UNINITIALIZED )
  {}

  virtual ~game_state_impl() {}

  void on_initialize() override
  {
    static_cast< strategy_t & >(*this).on_initialize();
    set_status( game_state_status::INITIALIZED );
  }
  
  void on_pause() override
  {
    static_cast< strategy_t & >(*this).on_pause();
    set_status( game_state_status::PAUSED );
  }

  void on_continue() override
  {
    static_cast< strategy_t & >(*this).on_continue();
    set_status( game_state_status::CONTINUING );
  }

  void on_deinitialize() override
  {
    static_cast< strategy_t & >(*this).on_deinitialize();
    set_status( game_state_status::DEINITIALIZING );
  } 

// Runnable
  void run() override
  {
    static_cast< strategy_t & >(*this).run();
  }

  void interrupt() override
  {
    static_cast< strategy_t & >(*this).interrupt();
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

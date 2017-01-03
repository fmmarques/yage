#if !defined(GAME_ENGINE_ABSTRACT_H)
#  define GAME_ENGINE_ABSTRACT_H

#include <memory>
#include <queue>

#include <engine/game_state.abstract.h>
#include <engine/game_engine.interface.h>

namespace engine {

class game_engine_abstract:
  public virtual engine::game_engine_interface {
protected:
  game_engine_abstract();
public:
  static std::shared_ptr< game_engine_abstract > instance();
  ~game_engine_abstract();

  void push( std::unique_ptr< engine::game_state_interface >&& rrState );
  std::unique_ptr< engine::game_state_interface >& peek();
  std::unique_ptr< engine::game_state_interface >& pop();
  
private:
  std::queue< std::unique_ptr< game_state_interface > > _qStates;
};

}

#endif

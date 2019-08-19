
#include <yage/engine/game_state.hpp>

namespace yage {
namespace engine {

game_state::game_state():
  status( engine::game_state_status::UNINITIALIZED )
{

}

game_state::~game_state()
{}

void game_state::on_initialize()
{
  set_status( game_state_status::INITIALIZED );
}

void game_state::on_pause()
{
  set_status( game_state_status::PAUSED );
}

void game_state::on_continue()
{
  set_status( game_state_status::CONTINUING );
}

void game_state::on_deinitialize()
{
  set_status( game_state_status::DEINITIALIZING );
}

const game_state_status& game_state::get_status() const
{
  return status;
}

void game_state::set_status(game_state_status&& status)
{
  this->status = status;
}

}
}

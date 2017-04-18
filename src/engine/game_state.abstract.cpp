
#include <engine/game_state.abstract.h>

namespace engine {

game_state_abstract::game_state_abstract():
  _eStatus( engine::game_state_status::UNINITIALIZED )
{

}

game_state_abstract::~game_state_abstract()
{}

void game_state_abstract::on_initialize()
{
  set_status( game_state_status::INITIALIZED );
}

void game_state_abstract::on_pause()
{
  set_status( game_state_status::PAUSED );
}

void game_state_abstract::on_continue()
{
  set_status( game_state_status::CONTINUING );
}

void game_state_abstract::on_deinitialize()
{
  set_status( game_state_status::DEINITIALIZING );
}

const game_state_status& game_state_abstract::get_status() const
{
  return _eStatus;
}

void game_state_abstract::set_status(game_state_status&& status)
{
  _eStatus = status;
}

}

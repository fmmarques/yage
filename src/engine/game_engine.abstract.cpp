#include <SDL2/SDL.h>

#include <engine/game_engine.abstract.h>

namespace engine {

  game_engine::invariant() 
  {
  }

  game_engine::game_engine():
  void game_engine<

  void game_engine::push( std::unique_ptr< engine::game_state_interface >&& rrState )
  {
  
  }
}

void events::event_manager::run()
{
  std::unique_lock<std::mutex> lLock(_mMutex, std::defer_lock);
  SDL_Event oEvent;
  unsigned int oEventType;
  do {
    
    while ( SDL_PollEvent(&oEvent) ) {
      oEventType = oEvent.type;
      switch( oEvent.type ) {
      case SDL_QUIT:
        lLock.lock();
	invariant();
	for ( auto itOverListByType: _mListeners ) 
	  for ( auto pListener: itOverListByType.second )
	    pListener->on_event( &oEvent );  
	invariant();
	lLock.unlock();
	_bContinue = false;
	break;
      default:
        lLock.lock();
	invariant();
	for ( auto pListener: _mListeners[ oEventType ] )
	  pListener->on_event( &oEvent );
	invariant();
	lLock.unlock();
	break;
      }
    }

  } while ( _bContinue );
  
  
}

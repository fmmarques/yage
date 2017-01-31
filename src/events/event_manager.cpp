#include <cassert>
#include <stdexcept>

#include <list>
#include <memory>
#include <mutex>

#include <SDL2/SDL.h>

#include <events/event_listener.interface.h>
#include <events/event_manager.h>

events::event_manager::event_manager():
  _mMutex(),
  _mListeners(),
  _bContinue(true)
{
  invariant();
}

void events::event_manager::invariant()
{

}

std::shared_ptr<events::event_manager>& events::event_manager::instance()
{
  static std::shared_ptr<events::event_manager> pInstance( new events::event_manager );
  return pInstance;
}

void events::event_manager::register_listener( 
  std::shared_ptr< events::event_listener_interface >& spListener,
  unsigned int event_t )
{
  std::unique_lock<std::mutex> lLock(_mMutex, std::defer_lock);

  lLock.lock();
  invariant();

  auto lListeners = _mListeners[ event_t ];
  lListeners.push_back( spListener );

  invariant();
  lLock.unlock();
}

void events::event_manager::unregister_listener( 
  std::shared_ptr< events::event_listener_interface >& spListener,
  unsigned int event_t )
{
  std::unique_lock<std::mutex> lLock(_mMutex, std::defer_lock);

  lLock.lock();
  invariant();

  auto lListeners = _mListeners[ event_t ];
  lListeners.remove( spListener );

  invariant();
  lLock.unlock();

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

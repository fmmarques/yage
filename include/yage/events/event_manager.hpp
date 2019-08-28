#if !defined(YAGE_EVENTS_EVENTMANAGER_H)
#  define YAGE_EVENTS_EVENTMANAGER_H

#include <stdint.h>
#include <map>
#include <list>
#include <vector>
#include <memory>
#include <shared_mutex>
#include <mutex>
#include <thread>

#include <SDL2/SDL.h>

#include <yage/events/event_listener.hpp>
#include <yage/engine/runnable.hpp>

namespace yage {
namespace events {

class event_manager:
  public virtual yage::engine::runnable
{
private:
  void invariant();
protected:
  event_manager();

  void emit(const SDL_Event& event);
public:
  static events::event_manager& instance();
  virtual ~event_manager();

  void subscribe( event_listener *listener,
                  SDL_EventType type);
  
  void subscribe( event_listener *listener,
		  std::vector< SDL_EventType >&& types);

  void unsubscribe( event_listener *listener,
                    SDL_EventType type );

  void unsubscribe( event_listener *listener,
		    std::vector< SDL_EventType >&& types ); 
  void interrupt() override;
  void run() override;
private:
  std::shared_mutex mutex;

  std::map< SDL_EventType, std::list< event_listener* > > event_listeners;
  bool continue_thread_execution;
  std::thread th;
};


}
}
#endif

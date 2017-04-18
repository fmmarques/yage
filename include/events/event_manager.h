#if !defined(EVENTS_EVENT_MANAGER_H)
#  define EVENTS_EVENT_MANAGER_H

#include <stdint.h>
#include <map>
#include <list>
#include <memory>
#include <mutex>


#include <SDL2/SDL.h>

#include <events/event_manager.interface.h>
#include <events/event_listener.interface.h>

namespace events {

class event_manager:
  public virtual event_manager_interface {
private:
  void invariant();
protected:
  event_manager();
public:
  static std::shared_ptr<event_manager>& instance();
  virtual ~event_manager();

  void register_listener( std::shared_ptr< event_listener_interface >& spListener,
                          uint
private:
  std::mutex _mMutex;

  std::map< uint32_t,
            std::list< std::shared_ptr< event_listener_interface > > > _mListeners;
};


}
#endif

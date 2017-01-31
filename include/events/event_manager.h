#if !defined(EVENTS_EVENT_MANAGER_H)
#  define EVENTS_EVENT_MANAGER_H

#include <list>
#include <map>
#include <memory>
#include <mutex>

#include <SDL2/SDL.h>

#include <events/event_listener.interface.h>

namespace events {

class event_manager {
protected:
  event_manager();
  void invariant();
public:
  
  static std::shared_ptr<event_manager>& instance();
  ~event_manager();

// Listener
  /// \brief Adds a listener to the event listener list
  /// \param spListener a shared pointer to the listener.
  void register_listener( std::shared_ptr< event_listener_interface >& spListener,
		          unsigned int event_t );
  /// \brief Removes a listener from the event listener list
  void unregister_listener( std::shared_ptr< event_listener_interface >& spListener,
		            unsigned int event_t );
  void run();
private:
  
  std::mutex _mMutex;

  std::map< unsigned int,
            std::list< std::shared_ptr< event_listener_interface > > > _mListeners;
  bool _bContinue;
};


}
#endif

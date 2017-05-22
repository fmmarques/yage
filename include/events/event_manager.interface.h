#if !defined(EVENTS_EVENT_MANAGER_INTERFACE)
#  define EVENTS_EVENT_MANAGER_INTERFACE

#include <memory>   // std::shared_ptr<T>
#include <stdint.h> // uint32_t

#include <events/event_listener.interface.h> 
namespace events {

struct event_manager_interface {
  /// \brief Adds a listener to the event listener list.
  /// \param spListener a shared pointer to the listener.
  /// \param event_t the event type to be listened
  virtual void register_listener( 
    std::shared_ptr< event_listener_interface >& spListener,
    uint32_t uiEvent ) = 0;

  /// \brief Removes a listener from the event listener list.
  /// \param event_t the event type listened to.
  virtual void unregister_listener( 
    std::shared_ptr< event_listener_interface >& spListener,
    uint32_t uiEvent ) = 0;
};

}

#endif

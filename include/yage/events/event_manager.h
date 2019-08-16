#if !defined(YAGE_EVENTS_EVENTMANAGER_H)
#  define YAGE_EVENTS_EVENTMANAGER_H

#include <stdint.h>
#include <map>
#include <list>
#include <memory>
#include <shared_mutex>
#include <mutex>


#include <SDL2/SDL.h>

#include <yage/events/event_listener.h>
#include <yage/engine/runnable.h>

namespace yage {
namespace events {


struct event_manager_interface {
  /// \brief Adds a listener to the event listener list.
  /// \param spListener a shared pointer to the listener.
  /// \param event_t the event type to be listened
  virtual void register_listener(
    event_listener *spListener,
    SDL_EventType uiEvent ) = 0;

  /// \brief Removes a listener from the event listener list.
  /// \param event_t the event type listened to.
  virtual void unregister_listener(
    event_listener *spListener,
    SDL_EventType uiEvent ) = 0;
};


class event_manager:
  public virtual yage::engine::runnable,
  public virtual yage::events::event_manager_interface {
private:
  void invariant();
protected:
  event_manager();

  void emit(const SDL_Event& event);
public:
  static events::event_manager& instance();
  virtual ~event_manager() = default;

  void register_listener( event_listener *listener,
                          SDL_EventType type) override;

  void unregister_listener( event_listener *listener,
                            SDL_EventType type ) override;

  void interrupt() override;
  void run() override;
private:
  std::shared_mutex mutex;

  std::map< SDL_EventType, std::list< event_listener* > > event_listeners;
  bool continue_thread_execution;
};


}
}
#endif

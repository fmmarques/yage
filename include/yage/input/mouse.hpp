#if !defined(YAGE_INPUT_MOUSE_HPP)
#  define YAGE_INPUT_MOUSE_HPP
#  include <mutex>

#  include <yage/utility.hpp>
#  include <yage/input/input_listener.hpp>

namespace yage {
namespace input {
namespace interface1 {

enum class mouse_event { UNDEFINED, SINGLE_CLICK, DOUBLE_CLICK, DRAG };

class mouse:
  public virtual yage::input::mouse_listener
{
private:
  enum EVENTS { CLICK = 0, DOUBLE_CLICK, DRAGGING, EVENT_COUNT };
private:
  mutable std::mutex m;
  SDL_Rect r;
  mouse_event e;
  bool s[EVENT_COUNT];
protected:
  mouse();
public:
  static mouse& instance();
  ~mouse();

  void on_mouse_button_up(const SDL_MouseButtonEvent& b);
  void on_mouse_button_down(const SDL_MouseButtonEvent& e);
  void on_mouse_movement(const SDL_MouseMotionEvent& e);
  
  bool hovers(const SDL_Rect& o_r);
  bool is_dragging();

};

}
}
}

#endif

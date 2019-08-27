#if !defined(YAGE_INPUT_MOUSE_HPP)
#  define YAGE_INPUT_MOUSE_HPP

#  include <yage/utility.hpp>
#  include <yage/input/input_listener.hpp>
#  include <yage/input/input_manager.hpp>

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
public:
  mouse():
    m{}
  , r{ .x = 0, .y = 0, .w = 1, .h = 1 }
  , e{ mouse_event::UNDEFINED }
  , s{ false, false, false }
  {
    input_manager::instance().subscribe(this);
  }  

  ~mouse()
  {
    input_manager::instance().unsubscribe(this);
  }

  void on_mouse_button_up(const SDL_MouseButtonEvent& b)
  {
    std::unique_lock<decltype(m)> l(m);
    r.x = b.x; r.y = b.y;
    s[CLICK] = s[DOUBLE_CLICK] = s[DRAGGING] = false;
  }


  void on_mouse_button_down(const SDL_MouseButtonEvent& e)
  {
    std::unique_lock<decltype(m)> l(m);
    r.x = e.x; r.y = e.y;
    
    s[CLICK] = s[DOUBLE_CLICK] = s[DRAGGING] = false;
    int index = CLICK;
    if (e.clicks == 2)
      index = DOUBLE_CLICK;
    s[index] = true;
  }  
  

  void on_mouse_movement(const SDL_MouseMotionEvent& e)
  {
    std::unique_lock<decltype(m)> l(m);
    r.x = e.x ; r.y = e.y;
    if (s[CLICK])
      s[DRAGGING]=true;
  }
  
  bool hovers(const SDL_Rect& o_r)
  {
    std::unique_lock<decltype(m)> l(m);
    return yage::utility::intersects(r,o_r);
  }

  bool is_dragging()
  {
    return s[DRAGGING];
  }
  
   
};

}
}
}

#endif

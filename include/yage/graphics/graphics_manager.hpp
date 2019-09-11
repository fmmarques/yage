#if !defined(GRAPHICS_GRAPHICS_MANAGER_H)
#  define GRAPHICS_GRAPHICS_MANAGER_H

#include <memory>
#include <string>

#include <SDL.h>

namespace yage {
namespace graphics {
namespace interface1 {

struct sdl_deleter_t
{
  void operator()(SDL_Window *ptr) const;
  void operator()(SDL_Renderer *ptr) const;
};


class window
{
public:
  window() {};
  window( const std::string& title, unsigned width, unsigned height ); 
  window(window&& other);
  window(const window&) = delete;
  window& operator=(const window&) = delete;

  operator SDL_Rect*();
  operator SDL_Window*();
  operator SDL_Renderer*();

  int w() const;
  int h() const;
private:
  int width;
  int height;
  std::string title;
  std::unique_ptr< SDL_Window, sdl_deleter_t > window_resource;
  std::unique_ptr<SDL_Renderer, sdl_deleter_t > renderer_resource;
  SDL_Rect rectangle;
};


class graphics_manager
{
protected:
  graphics_manager();
  void invariant() const;
public:
  static graphics_manager& instance();
  ~graphics_manager();

// Window related
  void set_window(window&& main_window);
  window& get_window() const;

// Renderer
  SDL_Renderer *get_renderer() const;

private:
  std::unique_ptr< window > main_window;
};

}
 using namespace interface1;
}
}

#endif

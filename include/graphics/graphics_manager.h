#if !defined(GRAPHICS_GRAPHICS_MANAGER_H)
#  define GRAPHICS_GRAPHICS_MANAGER_H

#include <memory>
#include <string>

#include <SDL2/SDL.h>

namespace graphics {

class graphics_manager
{
protected:
  graphics_manager();
  void invariant() const;
  
public:
  static std::unique_ptr<graphics::graphics_manager>& instance();
  ~graphics_manager();

// Window related
  SDL_Window* get_window()           const;
  const SDL_Rect&   get_window_rectangle() const;

  SDL_Window* create_window( const char *pWindowTitle = "", 
		             unsigned int uiWidth = graphics_manager::uiDefaultWindowWidth, 
			     unsigned int uiHeight = graphics_manager::uiDefaultWindowHeight );


  SDL_Renderer *get_renderer() const;

private:
  SDL_Window *pWindow;
  SDL_Rect oWindowRectangle;
  
  SDL_Renderer *pRenderer;
  
  static const unsigned int uiDefaultWindowWidth, uiDefaultWindowHeight;
  static const std::string sNoAvailableWindow;
  
};

}

#endif

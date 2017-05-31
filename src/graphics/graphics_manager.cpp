#include <cassert>
#include <stdexcept>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include <yage/graphics/graphics_manager.h>

const unsigned int graphics::graphics_manager::uiDefaultWindowWidth = 480;
const unsigned int graphics::graphics_manager::uiDefaultWindowHeight = 640;
const std::string graphics::graphics_manager::sNoAvailableWindow = "";

graphics::graphics_manager::graphics_manager():
  pWindow(0),
  oWindowRectangle{0, 0, 0, 0},
  pRenderer(0)
{
  using namespace std;

  if ( 0 != SDL_Init(SDL_INIT_VIDEO) )
    throw runtime_error( SDL_GetError() );

  if ( 0 != SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND) ) 
    throw std::runtime_error( SDL_GetError() );
}

void graphics::graphics_manager::invariant() const
{
  assert( "A instance of graphics manager must have a valid SDL_Window. " && 
	  0 != pWindow );
  assert( "If a instance of graphics manager has a valid SDL_Window then it must have a valid SDL_Renderer " && 
 	  (!(0 != pWindow) || 0 != pRenderer ) );
  assert( "If a instance of graphics manager has a valid SDL_Window then it must have a valid SDL_Rect with the window's dimensions." );
}

std::unique_ptr<graphics::graphics_manager>& graphics::graphics_manager::instance()
{
  static std::unique_ptr<graphics::graphics_manager> instance(new graphics::graphics_manager);
  return instance;
}


graphics::graphics_manager::~graphics_manager()
{
  invariant();
  if (0 != pRenderer)
    SDL_DestroyRenderer(pRenderer);
  if (0 != pWindow)
    SDL_DestroyWindow(pWindow);
}

SDL_Window* graphics::graphics_manager::get_window() const
{
  invariant();
  if (0 == pWindow)
    throw std::runtime_error(graphics::graphics_manager::sNoAvailableWindow);
  invariant();
  return pWindow;
}

const SDL_Rect& graphics::graphics_manager::get_window_rectangle() const
{
  invariant();
  if (0 == pWindow)
    throw std::runtime_error(graphics::graphics_manager::sNoAvailableWindow);
  invariant();
  return oWindowRectangle;
}

SDL_Window* graphics::graphics_manager::create_window( 
  const char * pWindowTitle,
  unsigned int uiWidth,
  unsigned int uiHeight )
{
  using namespace std;

  assert( "The title of the window must not be null." && 
	  nullptr != pWindowTitle );
  assert( "The width of the window must not be 0." && 
	  0 < uiWidth );
  assert( "The height of the window must not be 0." && 
	  0 < uiHeight );
  invariant();


  if (0 != pWindow) {
    if (0 != pRenderer) 
      SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
  }
  
  oWindowRectangle.x = oWindowRectangle.y = 0;
  oWindowRectangle.w = static_cast<int>( uiWidth );
  oWindowRectangle.h = static_cast<int>( uiHeight );

  pWindow = SDL_CreateWindow(  pWindowTitle,
		               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			       oWindowRectangle.w, oWindowRectangle.h,
			       SDL_WINDOW_OPENGL );
  if ( 0 == pWindow ) 
    throw runtime_error( SDL_GetError() );


  pRenderer = SDL_CreateRenderer( pWindow, 
		                   -1,
				   SDL_RENDERER_ACCELERATED );
  if ( 0 == pRenderer )
    throw runtime_error( SDL_GetError() );
  invariant();
  return pWindow;
}

SDL_Renderer* graphics::graphics_manager::get_renderer() const
{
  invariant();
  if (0 == pWindow)
    throw std::runtime_error( graphics::graphics_manager::sNoAvailableWindow);
  invariant();
  return pRenderer;
}


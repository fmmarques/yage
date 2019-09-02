#include <iostream>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include <yage/graphics/graphics_manager.hpp>

namespace yage {
namespace graphics {
namespace interface1 {


// Deleter
void sdl_deleter_t::operator()(SDL_Window *ptr) const 
{
  if (nullptr != ptr)
    SDL_DestroyWindow(ptr);
}	

void sdl_deleter_t::operator()(SDL_Renderer *ptr) const
{
  if (nullptr != ptr)
    SDL_DestroyRenderer(ptr);
}

window::window(
  const std::string& title,
  unsigned width,
  unsigned height):
  width(width),
  height(height),
	title(title),
 	window_resource{nullptr},
	renderer_resource{nullptr},
	rectangle{}
{
  (void) graphics_manager::instance();

  this->title = title;

  auto temp_window_ptr = SDL_CreateWindow( title.c_str() ,
		             SDL_WINDOWPOS_CENTERED, 
			     SDL_WINDOWPOS_CENTERED,
			     width, height,
			     SDL_WINDOW_OPENGL );
  if (nullptr == temp_window_ptr)
    throw std::runtime_error( "Couldn't create a SDL window with error: \"" + std::string( SDL_GetError() ) + "\"" );


  window_resource = std::unique_ptr< SDL_Window, sdl_deleter_t >( temp_window_ptr );
  
  auto temp_renderer_ptr =SDL_CreateRenderer(window_resource.get(), -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == temp_renderer_ptr)
    throw std::runtime_error( "Couldn't create a SDL renderer with error: \"" + std::string( SDL_GetError() ) + "\"" );
  renderer_resource = std::unique_ptr< SDL_Renderer, sdl_deleter_t >( temp_renderer_ptr );
  
  rectangle.x = rectangle.y = 0;
  rectangle.w = static_cast<int>( width );
  rectangle.h = static_cast<int>( height );
  
}

window::window(window&& other):
  width{other.width}
, height{other.height}
, title{other.title}
,  window_resource{std::move(other.window_resource)},
  renderer_resource{std::move(other.renderer_resource)},
  rectangle{other.rectangle}
{}

window::operator SDL_Rect*()
{
  return &rectangle; 
}

window::operator SDL_Window*()
{
  return window_resource.get();
}

window::operator SDL_Renderer*()
{
  return renderer_resource.get();
}

int window::w() const
{
  return width;
}

int window::h() const
{
  return height;
}

// Graphics manager
graphics_manager::graphics_manager():
  main_window(nullptr)
{
	const std::string fn{ std::string(__PRETTY_FUNCTION__) + std::string(": ") };
	using namespace std;
//	std::cout << fn << "entry" << std::endl;
  
	if ( 0 != SDL_InitSubSystem(SDL_INIT_VIDEO) )
		throw runtime_error("Couldn't initialize video with error: \"" + std::string(SDL_GetError()) + "\".");
  
//	std::cout << fn << "exit" << std::endl;
}

void graphics_manager::invariant() const
{
}

graphics_manager& graphics::graphics_manager::instance()
{
  static graphics::graphics_manager instance{};
  return instance;
}


graphics_manager::~graphics_manager()
{
	std::string fn{ std::string(__PRETTY_FUNCTION__) + std::string(": ") };
	std::cout << fn << "quitting video subsystem." << std::endl;
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	invariant();
}

void graphics_manager::set_window(window&& new_window)
{
	std::string fn{ std::string(__PRETTY_FUNCTION__) + std::string(": ") };
	std::cout << fn << "setting a new window."<< std::endl;
	main_window = std::make_unique< window >(std::move(new_window));
//	std::cout << fn << "exit" << std::endl;
}

window& graphics_manager::get_window() const
{
  invariant();
  if (nullptr == main_window)
    throw std::runtime_error("no window");
  invariant();
  return *(main_window.get());
}

SDL_Renderer *graphics_manager::get_renderer() const 
{
  invariant();
  return *main_window;
}
//  if ( 0 != SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) ) 
//    throw std::runtime_error( "SDL_SetRenderDrawBlendMode returned \"" + std::string( SDL_GetError() ) + "\"" );

}
}
}

#include <cassert>
#include <yage/widgets/button.hpp>
#include <yage/graphics/graphics_manager.hpp>
namespace yage {
  namespace widgets  {
    namespace interface1 {


button::button( const yage::graphics::font& f, 
                const std::string& t, 
                int ppt,
 //               const yage::graphics::texture& background, 
                const std::function< void() >& callback ):
  _l{ yage::widgets::label(f, t, (SDL_Color){ 0,0,0, 0 }, ppt) }
, _b{ nullptr }
, _c{callback}
{

  auto&& renderer = yage::graphics::graphics_manager::instance().get_window();
  SDL_Rect r { .x = 1, 1, 1, 1 };
  _b = std::unique_ptr< SDL_Texture, yage::graphics::__texture_deleter >(
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1, 1) );

  SDL_SetRenderTarget(renderer, _b.get());
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x0);
  SDL_RenderClear(renderer);
  SDL_RenderDrawRect(renderer,&r);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &r);
  SDL_SetRenderTarget(renderer, NULL);
}

void button::on_click()
{
  _c();
}

void button::render(const SDL_Rect* rect)
{
  assert(nullptr != rect);
  auto&& r = yage::graphics::graphics_manager::instance().get_window();
  
  SDL_Rect centered_label { .x = rect->x, rect->y, rect->w, rect->h };
  centered_label.x += ((rect->w)/2 - _l.w() / 2);
  centered_label.y += ((rect->h)/2 - _l.h() / 2);

  SDL_RenderCopy(r, _b.get(), NULL,rect);
  _l.render(&centered_label);
}

int button::h() const 
{
  return _l.h();
}

int button::w() const
{
  return _l.w();
}

}
}
}

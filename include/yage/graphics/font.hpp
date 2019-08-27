#if !defined(YAGE_GRAPHICS_FONT_HPP)
#  define YAGE_GRAPHICS_FONT_HPP

#  include <yage/graphics/texture_manager.hpp> // for deleters;

namespace yage {
namespace graphics {
namespace interface1 {

struct __font_deleter_wrapper_t
{
	void operator()(TTF_Font *);
};

class font_manager;
class font
{
private:
	std::string n;
	std::shared_ptr< TTF_Font > f;
	std::unique_ptr< SDL_Texture, __deleter_wrapper_t > t;
	stringstream ss;
protected:
	friend class font_manager;
	font(const std::string& name, std::shared_ptr< TTF_Font > font);
public:
	font(font&& other);
	font(const font& other);
	~font();

	font& operator=(font&& other);
	font& operator=(const font& other);

	font& operator<<(const std::string);
};


class font_manager
{
private:
	std::map< std::string, std::shared_ptr< TTF_Font > > fonts_by_name;

protected:
	font_manager();
	font_manager::font_manager() :
		fonts_by_name{}
	{}


public:
	static font_manager& instance() { static font_manager instance{}; return instance; }

	font load(const std::string& font, int ppt);
	font font_manager::load(const std::string font, int ppt)
	{
		auto&& it = cache.find(font);
		if (it != cache.end())
		{
			return font((*it)->second);
		}

		std::unique_ptr< TTF_Font, __font_deleter_wrapper_t > unique_font(TTF_OpenFont(font.c_str(), ppt));

		if (nullptr == unique_font)
			throw std::runtime_error(SDL_GetError());

		
		std::shared_ptr<SDL_Texture> shared_font(std::move(unique_font));
		fonts_by_name.emplace(name, shared_font);

		return graphics::font(shared_font);
	}
};

}
using namespace interface1;
}
}


TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

SDL_Rect Message_rect; //create a rect
Message_rect.x = 0;  //controls the rect's x coordinate 
Message_rect.y = 0; // controls the rect's y coordinte
Message_rect.w = 100; // controls the width of the rect
Message_rect.h = 100; // controls the height of the rect

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

//Don't forget too free your surface and texture

#endif
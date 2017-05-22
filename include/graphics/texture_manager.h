#if !defined(GRAPHICS_TEXTURE_MANAGER)
#  define GRAPHICS_TEXTURE_MANAGER

#include <memory>
#include <string>
#include <map>

#include <SDL2/SDL.h>

namespace graphics {

struct __deleter_wrapper_t {
  void operator()(SDL_Texture *);
  void operator()(SDL_Surface *);
};

class texture_manager
{
protected:
  void invariant() const;
  texture_manager();
public:
  static graphics::texture_manager& instance();
  ~texture_manager();

  /// \brief Loads a texture from a file.
  std::shared_ptr<SDL_Texture> load(const std::string&);


private:
  std::map< std::string,
	    std::shared_ptr< SDL_Texture > > _mTextureByFilename;
  int _iInitiatedFormats;
};

}
#endif

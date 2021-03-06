#if !defined(GRAPHICS_TEXTURE_MANAGER)
#  define GRAPHICS_TEXTURE_MANAGER

#include <memory>
#include <string>
#include <map>

#include <SDL.h>


namespace yage {
namespace graphics {
namespace interface1 {

struct __texture_deleter 
{
  void operator()(SDL_Texture *);
};

struct __surface_deleter
{
  void operator()(SDL_Surface *);
};

class texture;
class texture_manager
{
protected:
  void invariant() const;
  texture_manager();
public:
  static texture_manager& instance();
  ~texture_manager();

  /// \brief Loads a texture from a file.
  texture load(const std::string&);
  texture load(const std::string&, uint8_t r, uint8_t g, uint8_t b);

  void on_release(const texture& texture );
private:
  std::map< std::string,
	    std::shared_ptr< SDL_Texture > > textures_by_name;
  int formats;
};

}
using namespace interface1;
}
}
#endif

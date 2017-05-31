#if !defined(ENGINE_UPDATABLE_INTERFACE_H)
#  define ENGINE_UPDATABLE_INTERFACE_H

namespace engine {

struct updatable_interface
{
  virtual void on_update() = 0;
};

}
#endif

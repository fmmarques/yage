#if !defined(RUNNABLE_INTERFACE_H)
#  define RUNNABLE_INTERFACE_H

#include <memory>


namespace yage {
namespace engine {
//
struct runnable
{
  virtual ~runnable() {}

  virtual void run() = 0;
  virtual void interrupt() = 0;
};
}

}
#endif

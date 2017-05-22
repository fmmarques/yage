#if !defined(RUNNABLE_INTERFACE_H)
#  define RUNNABLE_INTERFACE_H

#include <memory>


namespace engine {
//
struct runnable_interface
{
  virtual ~runnable_interface() {}

  virtual void run() = 0;
  virtual void interrupt() = 0;
}; 

}
#endif

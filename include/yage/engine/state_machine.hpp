#if !defined(ENGINE_STATE_MACHINE_IMPLEMENTATION_H)
#  define ENGINE_STATE_MACHINE_IMPLEMENTATION_H

#include <stack>
#include <memory>

namespace yage {
namespace engine {


template < typename state_t >
class state_machine
{
private:
  std::stack< std::shared_ptr< state_t > > states;
protected:
  void invariant() const {}
public:
  virtual ~state_machine() {};

  state_machine():
    states{}
  {
  }

  template < class state_derived_t, class... args_t >
  void push(args_t&&... args)
  {
    if (!states.empty())
      (states.top().get())->on_pause();
    states.push(std::make_shared< state_derived_t >(args...));
    (states.top().get())->on_initialize();
  }

  virtual std::shared_ptr<state_t>&& pop()
  {
    auto&& result = std::move(states.top());
    result->on_deinitialize();
    states.pop();
    if (!states.empty())
      (states.top().get())->on_continue();
    return std::move(result);
  }

  virtual state_t* peek() const
  {
    return states.top().get();
  }

  virtual unsigned int length() const
  {
    return states.size();
  }

};

}
}

#endif

#if !defined(ENGINE_STATE_MACHINE_IMPLEMENTATION_H)
#  define ENGINE_STATE_MACHINE_IMPLEMENTATION_H

#include <queue>
#include <memory>

namespace yage {
namespace engine {


template < typename state_t >
class state_machine
{
public:
  virtual ~state_machine() {};

  state_machine():
    states{}
  {
  }

  state_machine(state_machine&& other):
    states()
  {
    states.swap(other.states);
  }



  virtual void push(state_t&& state)
  {
    states.push(state);
  }

  virtual state_t&& pop()
  {
    state_t result = std::move(states.front());
    states.pop();
    return std::move(result);
  }

  virtual state_t&& peek() const
  {
    return states.front();
  }

  virtual unsigned int length() const
  {
    return states.size();
  }

private:
  std::queue< std::unique_ptr< state_t > > states;
};

}
}

#endif

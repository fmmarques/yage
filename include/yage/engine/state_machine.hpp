#if !defined(ENGINE_STATE_MACHINE_IMPLEMENTATION_H)
#  define ENGINE_STATE_MACHINE_IMPLEMENTATION_H

#include <queue>
#include <memory>

namespace yage {
namespace engine {


template < typename state_t >
class state_machine
{
private:
  std::queue< std::unique_ptr< state_t > > states;
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


  template < typename state_derived_t >
  void push(state_derived_t&& state)
  {
    states.push(std::make_unique< state_derived_t>(state));
  }

  virtual state_t* pop()
  {
    auto&& result = std::move(states.front());
    states.pop();

    return std::move(result.release());
  }

  virtual state_t* peek() const
  {
    return states.front().get();
  }

  virtual unsigned int length() const
  {
    return states.size();
  }

};

}
}

#endif

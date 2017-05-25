#if !defined(ENGINE_STATE_MACHINE_IMPLEMENTATION_H)
#  define ENGINE_STATE_MACHINE_IMPLEMENTATION_H

#include <queue>
#include <memory>

namespace engine {

template < typename state_t >
struct state_machine_interface {
  virtual void push(state_t&& state) = 0;
  virtual state_t&& pop() = 0;

  virtual const state_t& peek() const = 0;
  virtual unsigned int length() const = 0;
};

template < typename state_t >
class state_machine: public virtual state_machine_interface< state_t >
{
public:
  typedef typename state_t::null_state_t null_state_t;

  virtual ~state_machine() {};

  state_machine():
    state_machine_interface< state_t >(),
    _qStates()
  {
    _qStates.emplace( std::move( null_state_t() ) );
  }

  state_machine(state_machine &&rrOther):
    state_machine_interface< state_t >(),
    _qStates() 
  {
    _qStates.swap(rrOther._qStates);  
  }

  state_machine(const state_machine &rOther):
    state_machine_interface< state_t >(),
    _qStates() 
    
  {
    for (state_t state: rOther._qStates)
      _qStates.emplace( state );
  } 

  virtual void push(state_t&& state)
  {
    _qStates.push(state);
  }

  virtual state_t&& pop() 
  {
    state_t result = std::move(_qStates.front());
    _qStates.pop();
    return std::move(result); 
  }

  virtual const state_t& peek() const
  {
    return _qStates.front();
  } 

  virtual unsigned int length() const 
  {
    return _qStates.size();
  }

private:
  std::queue< state_t > _qStates;  
};

}

#endif

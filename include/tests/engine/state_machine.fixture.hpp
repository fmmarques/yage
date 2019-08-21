#if !defined (TESTS_ENGINE_STATE_MACHINE_FIXTURE_HPP)
#  define TESTS_ENGINE_STATE_MACHINE_FIXTURE_HPP

#include <sstream>
#include <gtest/gtest.h>

#include <yage/engine/game_state.hpp>
#include <yage/engine/state_machine.hpp>


class simple_state:
  public yage::engine::game_state_impl< simple_state >
{
private:
  std::stringstream& oss;
public:
  simple_state(std::stringstream& ss):
    oss{ss}
  {
    oss << "ctor ";
  }

  virtual ~simple_state() {}
  void run() { oss << "run "; }
  void interrupt() { oss << "interrupt "; }
  void on_initialize() {}
  void on_pause() {}
  void on_continue() {}
  void on_deinitialize() {}

};

class state_machine_test: public ::testing::Test {
private:
protected:
  yage::engine::state_machine< yage::engine::game_state > subject;
  state_machine_test():
    subject {}
  {}

  void SetUp() override
  {
  }
};

#endif

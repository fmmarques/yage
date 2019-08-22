#include <tests/engine/state_machine.fixture.hpp>

#include <yage/engine/state_machine.hpp>

TEST_F(state_machine_test, push_and_pop)
{
  std::stringstream oss{};
  subject.push< simple_state >(oss);
  auto&& peek = subject.peek();
  peek->run();
  peek->interrupt();
  ASSERT_EQ( "ctor on_frame on_interrupt ", oss.str());

}

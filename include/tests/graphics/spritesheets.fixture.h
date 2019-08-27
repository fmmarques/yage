#if !defined(TESTS_GRAPHICS_SPRITESHEETS_FIXTURE_HPP)
#  define TESTS_GRAPHICS_SPRITESHEETS_FIXTURE_HPP

#include <gtest/gtest.h>

class spritesheet_fixture: public ::testing::Test
{
protected:
  spritesheet_fixture() {}
  virtual ~spritesheet_fixture(){}

  void SetUp() override {}
};

#endif

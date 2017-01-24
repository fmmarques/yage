#if !defined(TESTS_UNIT_GRAPHICS_GRAPHICS_FIXTURE_H)
#  define TESTS_UNIT_GRAPHICS_GRAPHICS_FIXTURE_H

class graphics_manager_test: public ::testing::Test {
protected:
  graphics_manager_test(): 
    bWindowCreated(false)
  {}

  virtual void SetUp() {}

  bool bWindowCreated;
 
};

#endif

#include <tests/unit/graphics/graphics.fixture.h>

#include <graphics/graphics_manager.h>

TEST_F(graphics_manager_test, GetInstance) {
  ASSERT_NE( 
    graphics::graphics_manager::instance(),
    nullptr
  );	     
}


TEST_F(graphics_manager_test, GetWindow_Without_CreateWindow) {
  if ( false == bWindowCreated ) {
    ASSERT_THROW( 
      graphics::graphics_manager::instance()->get_window(),
      std::runtime_error
    );
  } else {
    ASSERT_NE(
      graphics::graphics_manager::instance()->get_window(),
      nullptr
    );
  }

  SUCCEED();
}

TEST_F(graphics_manager_test, GetWindowRectangle_Without_CreateWindow) {
  if ( false == bWindowCreated ) {
    ASSERT_THROW(
      graphics::graphics_manager::instance()->get_window_rectangle(),
      std::runtime_error
    );
  }
  SUCCEED();
}

TEST_F(graphics_manager_test, GetRenderer_Without_CreateWindow) {
  if ( false == bWindowCreated ) {
    ASSERT_THROW(
      graphics::graphics_manager::instance()->get_renderer(),
      std::runtime_error
    );
  } else {
    ASSERT_NE(
      graphics::graphics_manager::instance()->get_renderer(),
      nullptr
    );
  }
  SUCCEED();     
}

TEST_F(graphics_manager_test, CreateWindow) {
  ASSERT_NE(
    graphics::graphics_manager::instance()->create_window( "Teste", 640, 480 ),
    nullptr
  );
  bWindowCreated = true;
  SUCCEED();
}



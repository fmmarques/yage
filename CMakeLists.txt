cmake_minimum_required(VERSION 2.6)
project(yage CXX)


# Setting the project's Cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")


# Dependencies
#  SDL dependencies.
find_package(SDL2)
if (NOT SDL2_FOUND)
  message(FATAL_ERROR "SDL2 was not fond on the system")
endif()
include_directories(${SDL2_INCLUDE_DIR})
link_libraries(${SDL2_LIBRARY})
set(SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR} PARENT_SCOPE)

find_package(SDL2_image)
if (NOT SDL2_IMAGE_FOUND)
  message(FATAL_ERROR "SDL2_image was not found on the system")
endif()
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
link_libraries(${SDL2_IMAGE_LIBRARIES})

find_package(SDL2_ttf REQUIRED)
if (NOT SDL2_IMAGE_FOUND)
  message(FATAL_ERROR "SDL2_image was not found on the system")
endif()
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
link_libraries(${SDL2_IMAGE_LIBRARIES})

#  GTest for unit testing
find_package(GTest)
if (NOT GTEST_FOUND OR !${GTEST_FOUND})
  message(FATAL_ERROR "Google's Gtest, a C++ unit testing library is not present on your system. Please obtain it from google's github.")
endif()
include_directories(${GTEST_INCLUDE_DIRS})
link_libraries(${GTEST_BOTH_LIBRARIES})

# Sources
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
set(YAGE_SRC
	src/engine/game_engine.abstract.cpp
	src/engine/game_state.abstract.cpp
	src/graphics/drawable.abstract.cpp
	
	src/engine/state_machine.implementation.cpp
	src/engine/states/null_state.concrete.cpp

	src/events/event_manager.cpp
	src/graphics/graphics_manager.cpp
	src/graphics/texture_manager.cpp

	src/input/input_manager.cpp)
# Targets
add_library(yage MODULE ${YAGE_SRC})
set_property(TARGET yage PROPERTY CXX_STANDARD 14)


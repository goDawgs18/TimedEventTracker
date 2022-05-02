cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BuildTests "Build all tests." ON) # Makes boolean 'test' available.
set(PROJECT_NAME MyProject)
set(VERSION_NUM 1.0)
project(${PROJECT_NAME} VERSION ${VERSION_NUM})


add_library(timedEventTracker_lib timedEventTracker.cpp)

################################
# Testing
################################
if (BuildTests)
  # This will fetch and add the googletest files for testing
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )
  FetchContent_MakeAvailable(googletest)

  enable_testing()

  ##############
  # Unit Tests
  ##############

  add_executable(runUnitTests unitTests.cpp)

  target_link_libraries(runUnitTests gtest gtest_main)

  target_link_libraries(runUnitTests timedEventTracker_lib)

  add_test(NAME run-tests COMMAND runUnitTests)

endif()

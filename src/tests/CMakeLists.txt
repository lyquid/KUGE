find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(KUGE_tests
  component_tests.cpp
  entity_tests.cpp
  system_tests.cpp
)

target_link_libraries(KUGE_tests GTest::GTest GTest::Main)
gtest_discover_tests(KUGE_tests)

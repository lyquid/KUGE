find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(KUGE_src_tests hello_test.cpp)
target_link_libraries(KUGE_src_tests GTest::GTest GTest::Main)
gtest_discover_tests(KUGE_src_tests)

add_executable(KUGE
  ../main.cpp
  component.cpp
  entity_manager.cpp
)
target_compile_features(KUGE PUBLIC cxx_std_17)
set_target_properties(KUGE PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(KUGE PRIVATE ${KUGE_SOURCE_DIR}/lib)
target_include_directories(KUGE PRIVATE ${KUGE_SOURCE_DIR}/lib/imgui)
target_include_directories(KUGE PRIVATE ${KUGE_SOURCE_DIR}/lib/pugixml)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	set(MY_DEBUG_OPTIONS /Wall /RTC)
	set(MY_RELEASE_OPTIONS /w3 /O2)
	target_compile_options(KUGE PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
	target_compile_options(KUGE PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	set(MY_DEBUG_OPTIONS -Wall -Wconversion -Wdouble-promotion -Weffc++ -Wextra -Wfloat-equal -Wmain -Wshadow -fstack-usage -pedantic -g3)
	set(MY_RELEASE_OPTIONS -O2)
	target_compile_options(KUGE PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
	target_compile_options(KUGE PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(MY_DEBUG_OPTIONS -Wall -Wconversion -Wdouble-promotion -Weffc++ -Wextra -Wfloat-equal -Wmain -Wshadow -pedantic -g3)
	set(MY_RELEASE_OPTIONS -O2)
	target_compile_options(KUGE PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
	target_compile_options(KUGE PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")
endif()

if(DEFINED CMAKE_TOOLCHAIN_FILE)
  # target_link_libraries(KUGE PRIVATE
  #   box2d::box2d
  #   GLEW::GLEW
  #   glm::glm
  #   imgui
  #   KUGE
  #   pugixml
  #   SDL2::SDL2
  #   SDL2_wrappers
  # )
else()
  # target_link_libraries(KUGE PRIVATE
  #   box2d::box2d
  #   GLEW::GLEW
  #   glm::glm
  #   imgui
  #   KUGE
  #   pugixml
  #   ${SDL2_LIBRARY}
  #   SDL2_wrappers
  # )
endif()

install(TARGETS KUGE RUNTIME DESTINATION ${BIN_DIR})

add_subdirectory(tests)

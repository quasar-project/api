find_package(Catch2 REQUIRED)

file(GLOB_RECURSE TEST_SOURCES "*.cc")

set(TEST_TARGET_NAME ${PROJECT_NAME}_test)

add_executable(${TEST_TARGET_NAME})
set_target_properties(${TEST_TARGET_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

target_sources(${TEST_TARGET_NAME} PRIVATE ${TEST_SOURCES})

target_compile_definitions(${TEST_TARGET_NAME}
  PRIVATE
  -DQUASAR_API_TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/c++/test_data"
)

target_link_libraries(${TEST_TARGET_NAME}
  PRIVATE
  quasar::api++
  Catch2::Catch2WithMain
)
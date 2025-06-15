cmake_minimum_required(VERSION 3.15)

include_guard(GLOBAL)

project(quasar-api-bundle
  DESCRIPTION "QuaSAR library C/C++ API"
  HOMEPAGE_URL "https://github.com/quasar-project/api"
  LANGUAGES C CXX
)

set(PROJECT_NAMESPACE "quasar::")
set(PROJECT_FULL_NAME "${PROJECT_NAMESPACE}api_bundle")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(QUASAR_API_TESTS "Build tests" OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if ("${CMAKE_GENERATOR}" MATCHES "^Visual Studio")
  set(CMAKE_GENERATOR_PLATFORM "x64" CACHE STRING "" FORCE)
endif ()

find_package(fmt REQUIRED)

add_subdirectory(c)
add_subdirectory(c++)

unset(BUILD_SHARED_LIBS CACHE)
unset(QUASAR_API_TESTS CACHE)
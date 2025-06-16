cmake_minimum_required(VERSION 3.15)

include_guard(GLOBAL)

if(NOT TARGET quasar::api)
  message(FATAL_ERROR "QuaSAR API C++ library must be built first. Please build the 'quasar-api' target before building 'quasar-api_pp'.")
endif()

project(quasar-api_pp
  DESCRIPTION "QuaSAR library C++ API"
  HOMEPAGE_URL "https://github.com/quasar-project/api"
  LANGUAGES C CXX
)

set(PROJECT_NAMESPACE "quasar::")
set(PROJECT_FULL_NAME "${PROJECT_NAMESPACE}api++")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if ("${CMAKE_GENERATOR}" MATCHES "^Visual Studio")
  set(CMAKE_GENERATOR_PLATFORM "x64" CACHE STRING "" FORCE)
endif ()

add_library(${PROJECT_NAME})
add_library(${PROJECT_FULL_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON
)

target_sources(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/private/crc16.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/private/exif.cc
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  quasar::api
  fmt::fmt
)

target_include_directories(${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>$<INSTALL_INTERFACE:include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (WIN32)
  if (BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE QUASAR_API_LIBRARY)
  else ()
    target_compile_definitions(${PROJECT_NAME} PUBLIC QUASAR_API_STATIC_LIBRARY)
  endif ()
endif ()

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} 
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/quasar> $<INSTALL_INTERFACE:include/quasar> ; DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

unset(BUILD_SHARED_LIBS CACHE)
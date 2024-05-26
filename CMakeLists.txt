cmake_minimum_required(VERSION 3.6)

project(
  source_location
  LANGUAGES CXX
  VERSION 0.1)

if(CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(
    FATAL_ERROR
      "Building in-source is not supported! Please use out-of-source build dir and remove ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/ directory and ${CMAKE_CURRENT_SOURCE_DIR}/CMakeCache.txt"
  )
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CTest)

option(SOURCE_LOCATION_BUILD_TESTS "Enable test targets" ON)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS ON)
  set(CMAKE_CXX_STANDARD 11)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(SOURCE_LOCATION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_LOCATION_HEADERS_DIR ${SOURCE_LOCATION_DIR}/include/)

add_compile_options(-Wall -Wextra -pedantic -Werror)

if(SOURCE_LOCATION_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

add_library(source_location INTERFACE)
add_library(nostd::source_location ALIAS source_location)

target_include_directories(
  source_location
  INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

set(SOURCE_LOCATION_CMAKE_CONFIG_DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/source_location")

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/source_locationConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/source_locationConfig.cmake
  INSTALL_DESTINATION ${SOURCE_LOCATION_CMAKE_CONFIG_DESTINATION})

install(
  TARGETS source_location
  EXPORT source_locationTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
  EXPORT source_locationTargets
  NAMESPACE nostd::
  DESTINATION ${SOURCE_LOCATION_CMAKE_CONFIG_DESTINATION})

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/source_locationConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion)

install(DIRECTORY ${SOURCE_LOCATION_HEADERS_DIR}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/source_locationConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/source_locationConfigVersion.cmake"
        DESTINATION ${SOURCE_LOCATION_CMAKE_CONFIG_DESTINATION})

set(SOURCE_LOCATION_PKGCONFIG_INSTALL_DIR
    "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig"
    CACHE PATH "Path where source_location.pc is installed")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/source_location.pc.in
               ${CMAKE_CURRENT_BINARY_DIR}/source_location.pc @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/source_location.pc
        DESTINATION ${SOURCE_LOCATION_PKGCONFIG_INSTALL_DIR})

include(CPack)

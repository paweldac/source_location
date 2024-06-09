cmake_minimum_required(VERSION 3.6)

project(
  source_location
  LANGUAGES CXX
  VERSION 0.4)

if(CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(
    FATAL_ERROR
      "Building in-source is not supported! Please use out-of-source build dir and remove ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/ directory and ${CMAKE_CURRENT_SOURCE_DIR}/CMakeCache.txt"
  )
endif()

include(GNUInstallDirs)
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

# When CMake v3.26 will be incorporated check for empty
# CMAKE_CXX_COMPILER_FRONTEND_VARIANT can be removed
# https://cmake.org/cmake/help/v3.26/variable/CMAKE_LANG_COMPILER_FRONTEND_VARIANT.html
add_compile_options(
  "$<$<AND:$<COMPILE_LANG_AND_ID:CXX,GNU,Clang,AppleClang>,$<OR:$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>,$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},>>>:-Werror;-Wall;-Wextra;-pedantic>"
)

add_compile_options(
  "$<$<AND:$<COMPILE_LANG_AND_ID:CXX,MSVC,Clang>,$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},MSVC>>:/WX;/W4>"
)

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

# Install source_location

set(SOURCE_LOCATION_INCLUDE_INSTALL_DIR
    ${CMAKE_INSTALL_INCLUDEDIR}/source_location
    CACHE PATH "Location of header files")

set(SOURCE_LOCATION_CMAKE_CONFIG_DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/source_location")

# Include files

install(DIRECTORY ${SOURCE_LOCATION_HEADERS_DIR}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(
  TARGETS source_location
  EXPORT source_locationTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# Install source_location CMake config files

install(
  EXPORT source_locationTargets
  DESTINATION ${SOURCE_LOCATION_CMAKE_CONFIG_DESTINATION}
  NAMESPACE nostd::
  FILE "source_locationConfigTargets.cmake")

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/source_locationConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/source_locationConfig.cmake
  INSTALL_DESTINATION ${SOURCE_LOCATION_CMAKE_CONFIG_DESTINATION})

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/source_locationConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/source_locationConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/source_locationConfigVersion.cmake"
        DESTINATION ${SOURCE_LOCATION_CMAKE_CONFIG_DESTINATION})

# Install source_location pkg-config file

set(SOURCE_LOCATION_PKGCONFIG_INSTALL_DIR
    "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig"
    CACHE PATH "Path where source_location.pc is installed")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/source_location.pc.in
               ${CMAKE_CURRENT_BINARY_DIR}/source_location.pc @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/source_location.pc
        DESTINATION ${SOURCE_LOCATION_PKGCONFIG_INSTALL_DIR})

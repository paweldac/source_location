cmake_minimum_required(VERSION 3.5)
project(source_location_examples)

set(CMAKE_CXX_STANDARD 11)

# generator expression to affect Multi-configuration generators like Visual
# Studio, Ninja Multi-Config
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin>)

set(EXAMPLE_APPLICATION_SOURCES example_app.cpp)

add_executable(source_location_example ${EXAMPLE_APPLICATION_SOURCES})

set_target_properties(
  source_location_example PROPERTIES OUTPUT_NAME "source_location_example"
                                     SUFFIX ".app")

if(EXAMPLES_USE_CMAKE_CMAKE_CONFIG)
  message("Using exported cmake config.")
  find_package(source_location CONFIG REQUIRED)
  target_link_libraries(source_location_example PUBLIC nostd::source_location)
else()
  message("Using PkgConfig.")
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(PKG_SOURCE_LOCATION REQUIRED IMPORTED_TARGET
                    source_location)
  target_link_libraries(source_location_example
                        PUBLIC PkgConfig::PKG_SOURCE_LOCATION)
endif()

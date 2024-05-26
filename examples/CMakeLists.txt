cmake_minimum_required(VERSION 3.5)
project(source_location_examples)

set(CMAKE_CXX_STANDARD 11)

set(EXAMPLE_APPLICATION_SOURCES example_app.cpp)

add_executable(source_location_example.app ${EXAMPLE_APPLICATION_SOURCES})

if(EXAMPLES_USE_CMAKE_CMAKE_CONFIG)
  message("Using exported cmake config.")
  find_package(source_location CONFIG REQUIRED)
  target_link_libraries(source_location_example.app
                        PUBLIC nostd::source_location)
else()
  message("Using PkgConfig.")
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(PKG_SOURCE_LOCATION REQUIRED IMPORTED_TARGET
                    source_location)
  target_link_libraries(source_location_example.app
                        PUBLIC PkgConfig::PKG_SOURCE_LOCATION)
endif()

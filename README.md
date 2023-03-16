# source_location [![Build Status](https://travis-ci.org/paweldac/source_location.svg?branch=master)](https://travis-ci.org/paweldac/source_location)

Implementation of [source_location](https://en.cppreference.com/w/cpp/utility/source_location) for pre-c++20 projects. Enables improved logging/debugging experience. This implementation is a drop-in replacement for official source_location. After your project moves to c++20 standard, you can simply remove this dependency and use source_location provided by `<source_location>` header in standard library.

## Requirements

source_location requires at least c++11 standard.

## Supported platforms/compilers

Current implementation should compile on all platforms/compilers, but will work only some of them.

Supported plaforms:
- Linux

Supported compilers:
- GCC starting from version 4.8
- Clang starting from version 9.0
- MSVC starting from version 1925

On unsupported platforms/compilers:
- instead of file_name/function_name it will print 'unsupported'
- instead of line/column it will print '0'

`column()` functionality is supported only on Clang.

## How to use source_location

In c++ files, where you want to use source_location library import `<source_location.hpp>`. To obtain source_location information please, use static method `current()`. Example:
```c++
#include <iostream>
#include <source_location/source_location.hpp>

void foo()
{
    auto location = nostd::source_location::current();
    std::cout << location.file_name() << ":" << location.line() << ":"
              << location.column() << ":" << location.function_name() << ": "
              << "Hello World!" << std::endl;
}
```

Output from [example_app.cpp](https://raw.githubusercontent.com/paweldac/source_location/master/examples/example_app.cpp):
```
$ ./source_location.example
$ /home/travis/build/paweldac/source_location/examples/example_app.cpp:6:0:main: Hello World!
```

## How to integrate source_location with any C++ project

The simplest way to download [source_location.hpp](https://raw.githubusercontent.com/paweldac/source_location/master/include/source_location/source_location.hpp) and include it as any other header file in project.

Alternative way is to install source_location using CMake package. In order to install source_location from the repository:
```
$ git clone https://github.com/paweldac/source_location.git
$ cd source_location
$ mkdir build && cd build
$ cmake -DSOURCE_LOCATION_BUILD_TESTS=OFF ..
$ sudo make install
```

If you don't have sudo rights or want to install source_location to non-default location you need to specify [CMAKE_INSTALL_PREFIX](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html):
```
$ cmake -DSOURCE_LOCATION_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX="my/prefix/root/location" ..
$ make install
```

After installation you can either use exported CMake target or pkg-config file. 
For importing source_location from exported CMake target you need use [find_package()](https://cmake.org/cmake/help/latest/command/find_package.html):
```cmake
find_package(source_location CONFIG REQUIRED)
target_link_libraries(my_target_name nostd::source_location)
```
If you installed source_location to alternative location, you have to pass it to CMake as [CMAKE_FIND_ROOT_PATH](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html) variable.

For using pkg-config you need to use [pkg_check_modules()](https://cmake.org/cmake/help/latest/module/FindPkgConfig.html#command:pkg_check_modules):
```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(PKG_SOURCE_LOCATION REQUIRED IMPORTED_TARGET source_location)
target_link_libraries(my_target_name PkgConfig::PKG_SOURCE_LOCATION)
```
If you installed source_location to alternative location, you have to pass it to CMake as [CMAKE_PREFIX_PATH](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html) variable.

## CI verification

Platforms verifed by Travis CI:
- Linux
- Mac

Compilers verified by Travis CI:
- Clang 8/9/10
- GCC 4.8/5/6/7/8/9
- Xcode 11.3

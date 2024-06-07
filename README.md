# source_location [![nonstd::source_location CI](https://github.com/paweldac/source_location/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/paweldac/source_location/actions/workflows/ci.yml)

This repository provides an implementation of [source_location](https://en.cppreference.com/w/cpp/utility/source_location) for pre-C++20 projects, facilitating enhanced logging and debugging capabilities. This implementation is intended as a drop-in replacement for the official `std::source_location`. Once your project adopts the C++20 standard, you can seamlessly remove this dependency and utilize the `std::source_location` provided by the `<source_location>` header in the standard library.

## Requirements

The source_location requires at least the C++11 standard.

## Supported Platforms and Compilers

While this implementation should compile across all platforms and compilers, it is fully functional only on certain configurations.

Supported platforms:

- Linux
- macOS

Supported compilers:

- GCC from version 4.8 onward
- Clang from version 9.0 onward
- AppleClang from version 11.0.3 (included in Xcode version 11.4) onward
- Microsoft C/C++ compiler 19.29 (included in Visual Studio 2019 version 16.10) onward

On unsupported compilers, the output will be as follows:

- The `file_name()` and `function_name()` will display 'unsupported'
- The `line()` and `column()` will display '0'

The `column()` functionality is only supported on Clang and Microsoft.

## Usage

To use the source_location library in your C++ projects, include `<source_location.hpp>`. The `current()` static method is used to obtain source location information. Example:

```C++
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

## Example Output

Output from [example_app.cpp](https://raw.githubusercontent.com/paweldac/source_location/master/examples/example_app.cpp):

Supported compiler:

```sh
./source_location_example.app
/home/runner/work/source_location/source_location/examples/example_app.cpp:6:21:main: Hello World!
```

Unsupported compiler:

```sh
./source_location_example.app
unsupported:0:0:unsupported: Hello World!
```

## Integration with C++ Projects

The most straightforward method is to download [source_location.hpp](https://raw.githubusercontent.com/paweldac/source_location/master/include/source_location/source_location.hpp), put it into your project tree, and include it as you would any other header file.

An alternative way is to install source_location using the CMake package. To install from the repository:

```sh
git clone https://github.com/paweldac/source_location.git
cd source_location
mkdir build && cd build
cmake -DSOURCE_LOCATION_BUILD_TESTS=OFF ..
sudo make install
```

If you don't have sudo privileges or wish to install source_location to a non-default location, specify the [CMAKE_INSTALL_PREFIX](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html):

```sh
cmake -DSOURCE_LOCATION_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX="my/prefix/root/location" ..
make install
```

After installation, you can use either an exported CMake target or a pkg-config file.

To import source_location from an exported CMake target, use [find_package()](https://cmake.org/cmake/help/latest/command/find_package.html):

```cmake
find_package(source_location CONFIG REQUIRED)
target_link_libraries(my_target_name nostd::source_location)
```

For pkg-config integration, use [pkg_check_modules()](https://cmake.org/cmake/help/latest/module/FindPkgConfig.html#command:pkg_check_modules):

```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(PKG_SOURCE_LOCATION REQUIRED IMPORTED_TARGET source_location)
target_link_libraries(my_target_name PkgConfig::PKG_SOURCE_LOCATION)
```

If source_location is installed to a non-default location, pass it to CMake via the [CMAKE_PREFIX_PATH](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html) variable:

```sh
cmake -DCMAKE_PREFIX_PATH="my/prefix/root/location" ..
```

## GitHub Actions Workflow Verification

Platforms:

- Linux
- Mac

Compilers:

- Clang 10/11/12/13/14/15
- GCC 9/10/11/12
- Xcode 15.0.1

Previously verified compilers on Travis CI:

- Clang 8/9/10
- GCC 4.8/5/6/7/8/9
- Xcode 11.3 (unsupported at that time)

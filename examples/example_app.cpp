#include <iostream>
#include <source_location/source_location.hpp>

int main(int, char*[])
{
    auto location = nostd::source_location::current();
    std::cout << location.file_name() << ":" << location.line() << ":"
              << location.column() << ":" << location.function_name() << ": "
              << "Hello World!" << std::endl;
    return 0;
}
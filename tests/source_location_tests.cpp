#define CATCH_CONFIG_MAIN

#include "source_location/source_location.hpp"
#include <catch.hpp>
#include <string>

namespace {
const std::string fileName = "FileName.cpp";
const std::string functionName = "Namespace::FunctionName";
const auto lineNum = 1u;
const auto columnNum = 10u;
} // namespace

TEST_CASE("source_location::current with passed parameters shall return valid "
          "source_location with same data")
{
    auto sourceLocation = nostd::source_location::current(
        fileName.c_str(), functionName.c_str(), lineNum, columnNum);
    REQUIRE(sourceLocation.file_name() == fileName);
    REQUIRE(sourceLocation.function_name() == functionName);
    REQUIRE(sourceLocation.line() == lineNum);
    REQUIRE(sourceLocation.column() == columnNum);
}
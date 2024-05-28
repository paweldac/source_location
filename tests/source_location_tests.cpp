#define CATCH_CONFIG_MAIN

#include "source_location/source_location.hpp"
#include <catch.hpp>
#include <string>
#include <type_traits>

// https://www.open-std.org/JTC1/SC22/WG21/docs/papers/2019/p1208r6.pdf

// Cpp17DefaultConstructible, Cpp17CopyConstructible, Cpp17CopyAssignable, and Cpp17Destructible
static_assert(std::is_nothrow_default_constructible<nostd::source_location>::value, "s_nothrow_default_constructible<nostd::source_location> false");
static_assert(std::is_nothrow_copy_constructible<nostd::source_location>::value, "is_nothrow_copy_constructible<nostd::source_location> false");
static_assert(std::is_nothrow_copy_assignable<nostd::source_location>::value, "is_nothrow_copy_assignable<nostd::source_location> false");
static_assert(std::is_nothrow_destructible<nostd::source_location>::value, "is_nothrow_destructible<nostd::source_location> false");

// All of the following conditions are true :
//  —(3.1)is_nothrow_move_constructible_v<source_location>
//  —(3.2)is_nothrow_move_assignable_v<source_location>
//  —(3.3)is_nothrow_swappable_v<source_location>

static_assert(std::is_nothrow_move_constructible<nostd::source_location>::value, "is_nothrow_move_constructible<nostd::source_location> false");
static_assert(std::is_nothrow_move_assignable<nostd::source_location>::value, "is_nothrow_move_assignable<nostd::source_location> false");
#if not defined(__apple_build_version__)
static_assert(std::is_nothrow_swappable<nostd::source_location>::value, "is_nothrow_swappable<nostd::source_location> false");
#else
static_assert(std::__is_nothrow_swappable<nostd::source_location>::value, "__is_nothrow_swappable<nostd::source_location> false");
#endif

namespace {
const std::string fileName = "FileName.cpp";
const std::string functionName = "Namespace::FunctionName";
const auto lineNum = 1u;
const auto columnNum = 10u;
const std::string otherFileName = "OtherFileName.cpp";
const std::string otherFunctionName = "Namespace::OtherFunctionName";
const auto otherLineNum = 2;
const auto otherColumnNum = 20u;
} // namespace

// Lvalues of type source_location are swappable
TEST_CASE("Lvalues of type source_location are swappable")
{
    auto sourceLocation = nostd::source_location::current(
        fileName.c_str(), functionName.c_str(), lineNum, columnNum);
    auto otherSourceLocation = nostd::source_location::current(
        otherFileName.c_str(), otherFunctionName.c_str(), otherLineNum, otherColumnNum);

    std::swap(sourceLocation, otherSourceLocation);

    REQUIRE(sourceLocation.file_name() == otherFileName);
    REQUIRE(sourceLocation.function_name() == otherFunctionName);
    REQUIRE(sourceLocation.line() == otherLineNum);
    REQUIRE(sourceLocation.column() == otherColumnNum);

    REQUIRE(otherSourceLocation.file_name() == fileName);
    REQUIRE(otherSourceLocation.function_name() == functionName);
    REQUIRE(otherSourceLocation.line() == lineNum);
    REQUIRE(otherSourceLocation.column() == columnNum);
}

// The copy/move constructors and the copy/move assignment operators of source_location meet the following postconditions : Given two objects lhs and rhs of type source_location, where lhs 2 is a copy / move result of rhs, and where rhs_p is a value denoting the state of rhs before the corresponding copy / move operation, then each of the following conditions is true :
// -(6.1) strcmp(lhs.file_name(), rhs_p.file_name()) == 0
// —(6.2) strcmp(lhs.function_name(), rhs_p.function_name()) == 0
// —(6.3) lhs.line() == rhs_p.line()
// —(6.4) lhs.column() == rhs_p.column()

void verify_constructors_and_assigment_operators_postconditions(const nostd::source_location& lhs, const nostd::source_location& rhs_p)
{
    REQUIRE(strcmp(lhs.file_name(), rhs_p.file_name()) == 0);
    REQUIRE(strcmp(lhs.function_name(), rhs_p.function_name()) == 0);
    REQUIRE(lhs.line() == rhs_p.line());
    REQUIRE(lhs.column() == rhs_p.column());
}

TEST_CASE("Requirements on source_location copy constructor")
{
    auto rhs = nostd::source_location::current(
        fileName.c_str(), functionName.c_str(), lineNum, columnNum);
    auto rhs_p = rhs;
    auto lhs(rhs);
    verify_constructors_and_assigment_operators_postconditions(lhs, rhs_p);
}

TEST_CASE("Requirements on source_location copy assignment")
{
    auto rhs = nostd::source_location::current(
        fileName.c_str(), functionName.c_str(), lineNum, columnNum);
    auto rhs_p = rhs;
    auto lhs = rhs;
    verify_constructors_and_assigment_operators_postconditions(lhs, rhs_p);
}

TEST_CASE("Requirements on source_location move constructor")
{
    auto rhs = nostd::source_location::current(
        fileName.c_str(), functionName.c_str(), lineNum, columnNum);
    auto rhs_p = rhs;
    auto lhs(std::move(rhs));
    verify_constructors_and_assigment_operators_postconditions(lhs, rhs_p);
}

TEST_CASE("Requirements on source_location move assignment")
{
    auto rhs = nostd::source_location::current(
        fileName.c_str(), functionName.c_str(), lineNum, columnNum);
    auto rhs_p = rhs;
    auto lhs = std::move(rhs);
    verify_constructors_and_assigment_operators_postconditions(lhs, rhs_p);
}

bool stringEndsWith(std::string const& str, std::string const& ending)
{
    if (str.length() >= ending.length()) {
        return (0 == str.compare(str.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void test_source_location_current()
{
    const auto sourceLocation = nostd::source_location::current();
#if (not defined(__apple_build_version__) and defined(__clang__) and (__clang_major__ >= 9)) or (defined(__GNUC__) and (__GNUC__ > 4 or (__GNUC__ == 4 and __GNUC_MINOR__ >= 8)))
    REQUIRE(sourceLocation.line() == __LINE__ - 2);
#if defined(__clang__)
    REQUIRE(sourceLocation.column() == 33);
#else
    REQUIRE(sourceLocation.column() == 0);
#endif
    REQUIRE(0 == strcmp(sourceLocation.function_name(), "test_source_location_current"));
    REQUIRE(stringEndsWith(sourceLocation.file_name(), "source_location_tests.cpp"));
#else
    REQUIRE(sourceLocation.line() == 0);
    REQUIRE(sourceLocation.column() == 0);
    REQUIRE(0 == strcmp(sourceLocation.function_name(), "unsupported"));
    REQUIRE(0 == strcmp(sourceLocation.file_name(), "unsupported"));
#endif
}

TEST_CASE("source_location::current default behaviour")
{
    test_source_location_current();
}

TEST_CASE("source_location::current with passed parameters shall return valid source_location with same data")
{
    auto sourceLocation = nostd::source_location::current(
        fileName.c_str(), functionName.c_str(), lineNum, columnNum);
    REQUIRE(sourceLocation.file_name() == fileName);
    REQUIRE(sourceLocation.function_name() == functionName);
    REQUIRE(sourceLocation.line() == lineNum);
    REQUIRE(sourceLocation.column() == columnNum);
}
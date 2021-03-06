#include <sstream>

#include "ConfigurationStreamParameter_test.hpp"

#include "ConfigurationStreamParameter.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration::StreamParameter_test);

//=============================================================================================
void Configuration::StreamParameter_test::addTestCases()
{
    ADD_TEST_CASE(FromString);
    ADD_TEST_CASE(ToString);
    ADD_TEST_CASE(OperatorStreamExtraction);
    ADD_TEST_CASE(OperatorStreamInsertion);
}

//=============================================================================================
void Configuration::StreamParameter_test::FromString::addTestCases()
{
    ADD_TEST_CASE(Bool);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
void Configuration::StreamParameter_test::ToString::addTestCases()
{
    ADD_TEST_CASE(Bool);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
void Configuration::StreamParameter_test::OperatorStreamExtraction::addTestCases()
{
    ADD_TEST_CASE(Bool);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
void Configuration::StreamParameter_test::OperatorStreamInsertion::addTestCases()
{
    ADD_TEST_CASE(Bool);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
template <class T> Test::Result Configuration::StreamParameter_test::FromString::test(
    const std::string& initial_value, const T& should_equal)
{
    StreamParameter<T> temp;
    temp.fromString(initial_value);

    MUST_BE_TRUE(temp.getValue() == should_equal);

    return Test::PASSED;
}

//=============================================================================================
template <class T> Test::Result Configuration::StreamParameter_test::ToString::test(
    const T& initial_value, const std::string& should_equal)
{
    StreamParameter<T> temp(initial_value);

    std::string temp_string;
    temp.toString(temp_string);

    MUST_BE_TRUE(temp_string == should_equal);

    return Test::PASSED;
}

//=============================================================================================
template <class T>
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::test(
    const T& initial_value, const std::string& should_equal)
{
    StreamParameter<T> parameter(initial_value);

    std::ostringstream outstream;
    outstream << parameter;

    MUST_BE_TRUE(outstream.str() == should_equal);

    return Test::PASSED;
}

//=============================================================================================
template <class T>
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::test(
    const std::string& initial_value, const T& should_equal)
{
    StreamParameter<T> parameter;

    std::istringstream instream(initial_value);
    instream >> parameter;

    MUST_BE_TRUE(parameter.getValue() == should_equal);

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::Bool::body()
{
    return test<bool>("0", false);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::String::body()
{
    return test<std::string>("abcd", "abcd");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::Char::body()
{
    return test<char>("a", 'a');
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::Double::body()
{
    return test<double>("2.0", 2.0);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::Float::body()
{
    return test<float>("2.0", 2.0f);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::Int::body()
{
    return test<int>("3", 3);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::Long::body()
{
    return test<long>("4", 4);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::LongDouble::body()
{
    return test<long double>("5.0", 5.0l);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::LongLong::body()
{
    return test<long long>("6", 6ll);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::Short::body()
{
    return test<short>("7", 7);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::UnsignedChar::body()
{
    return test<unsigned char>("x", 'x');
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::UnsignedInt::body()
{
    return test<unsigned int>("9", 9u);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::UnsignedLong::body()
{
    return test<unsigned long>("44", 44ul);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::UnsignedLongLong::body()
{
    return test<unsigned long long>("12", 12ull);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::FromString::UnsignedShort::body()
{
    return test<unsigned short>("13", 13);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::Bool::body()
{
    return test<bool>(true, "1");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::String::body()
{
    return test<std::string>("1", "1");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::Char::body()
{
    return test<char>('a', "a");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::Double::body()
{
    return test<double>(14.333, "14.333");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::Float::body()
{
    return test<float>(13.2f, "13.2");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::Int::body()
{
    return test<int>(4, "4");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::Long::body()
{
    return test<long>(234, "234");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::LongDouble::body()
{
    return test<long double>(987.4l, "987.4");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::LongLong::body()
{
    return test<long long>(10000, "10000");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::Short::body()
{
    return test<short>(-111, "-111");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::UnsignedChar::body()
{
    return test<unsigned char>('9', "9");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::UnsignedInt::body()
{
    return test<unsigned int>(56791, "56791");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::UnsignedLong::body()
{
    return test<unsigned long>(99999, "99999");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::UnsignedLongLong::body()
{
    return test<unsigned long long>(11223344, "11223344");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::ToString::UnsignedShort::body()
{
    return test<unsigned short>(7766, "7766");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::Bool::body()
{
    return test<bool>("1", true);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::String::body()
{
    return test<std::string>("abcd", "abcd");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::Char::body()
{
    return test<char>("a", 'a');
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::Double::body()
{
    return test<double>("2.0", 2.0);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::Float::body()
{
    return test<float>("2.0", 2.0f);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::Int::body()
{
    return test<int>("3", 3);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::Long::body()
{
    return test<long>("4", 4);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::LongDouble::body()
{
    return test<long double>("5.0", 5.0l);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::LongLong::body()
{
    return test<long long>("6", 6ll);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::Short::body()
{
    return test<short>("7", 7);
}

//=============================================================================================
Test::Result
Configuration::StreamParameter_test::OperatorStreamExtraction::UnsignedChar::body()
{
    return test<unsigned char>("x", 'x');
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamExtraction::UnsignedInt::body()
{
    return test<unsigned int>("9", 9u);
}

//=============================================================================================
Test::Result
Configuration::StreamParameter_test::OperatorStreamExtraction::UnsignedLong::body()
{
    return test<unsigned long>("44", 44ul);
}

//=============================================================================================
Test::Result
Configuration::StreamParameter_test::OperatorStreamExtraction::UnsignedLongLong::body()
{
    return test<unsigned long long>("12", 12ull);
}

//=============================================================================================
Test::Result
Configuration::StreamParameter_test::OperatorStreamExtraction::UnsignedShort::body()
{
    return test<unsigned short>("13", 13);
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::Bool::body()
{
    return test<bool>(false, "0");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::String::body()
{
    return test<std::string>("1", "1");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::Char::body()
{
    return test<char>('a', "a");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::Double::body()
{
    return test<double>(14.333, "14.333");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::Float::body()
{
    return test<float>(13.2f, "13.2");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::Int::body()
{
    return test<int>(4, "4");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::Long::body()
{
    return test<long>(234, "234");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::LongDouble::body()
{
    return test<long double>(987.4l, "987.4");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::LongLong::body()
{
    return test<long long>(10000, "10000");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::Short::body()
{
    return test<short>(-111, "-111");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::UnsignedChar::body()
{
    return test<unsigned char>('9', "9");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::UnsignedInt::body()
{
    return test<unsigned int>(56791, "56791");
}

//=============================================================================================
Test::Result Configuration::StreamParameter_test::OperatorStreamInsertion::UnsignedLong::body()
{
    return test<unsigned long>(99999, "99999");
}

//=============================================================================================
Test::Result
Configuration::StreamParameter_test::OperatorStreamInsertion::UnsignedLongLong::body()
{
    return test<unsigned long long>(11223344, "11223344");
}

//=============================================================================================
Test::Result
Configuration::StreamParameter_test::OperatorStreamInsertion::UnsignedShort::body()
{
    return test<unsigned short>(7766, "7766");
}

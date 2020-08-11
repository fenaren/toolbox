#include <sstream>

#include "ConfigurationSimpleParameter_test.hpp"

#include "ConfigurationSimpleParameter.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration::SimpleParameter_test);

//=============================================================================================
void Configuration::SimpleParameter_test::addTestCases()
{
    ADD_TEST_CASE(FromString);
    ADD_TEST_CASE(ToString);
    ADD_TEST_CASE(OperatorStreamExtraction);
    ADD_TEST_CASE(OperatorStreamInsertion);
}

//=============================================================================================
void Configuration::SimpleParameter_test::FromString::addTestCases()
{
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
void Configuration::SimpleParameter_test::ToString::addTestCases()
{
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
void Configuration::SimpleParameter_test::OperatorStreamExtraction::addTestCases()
{
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
void Configuration::SimpleParameter_test::OperatorStreamInsertion::addTestCases()
{
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
template <class T> Test::Result Configuration::SimpleParameter_test::FromString::test(
    const std::string& initial_value, const T& should_equal)
{
    SimpleParameter<T> temp;
    temp.fromString(initial_value);

    MUST_BE_TRUE(temp.getValue() == should_equal);

    return Test::PASSED;
}

//=============================================================================================
template <class T> Test::Result Configuration::SimpleParameter_test::ToString::test(
    const T& initial_value, const std::string& should_equal)
{
    SimpleParameter<T> temp(initial_value);

    std::string temp_string;
    temp.toString(temp_string);

    MUST_BE_TRUE(temp_string == should_equal);

    return Test::PASSED;
}

//=============================================================================================
template <class T>
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::test(
    const T& initial_value, const std::string& should_equal)
{
    Configuration::SimpleParameter<T> parameter(initial_value);

    std::ostringstream outstream;
    outstream << parameter;

    MUST_BE_TRUE(outstream.str() == should_equal);

    return Test::PASSED;
}

//=============================================================================================
template <class T>
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::test(
    const std::string& initial_value, const T& should_equal)
{
    Configuration::SimpleParameter<T> parameter;

    std::istringstream instream(initial_value);
    instream >> parameter;

    MUST_BE_TRUE(parameter.getValue() == should_equal);

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::String::body()
{
    return test<std::string>("abcd", "abcd");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::Char::body()
{
    return test<char>("a", 'a');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::Double::body()
{
    return test<double>("2.0", 2.0);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::Float::body()
{
    return test<float>("2.0", 2.0f);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::Int::body()
{
    return test<int>("3", 3);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::Long::body()
{
    return test<long>("4", 4);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::LongDouble::body()
{
    return test<long double>("5.0", 5.0l);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::LongLong::body()
{
    return test<long long>("6", 6ll);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::Short::body()
{
    return test<short>("7", 7);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::UnsignedChar::body()
{
    return test<unsigned char>("x", 'x');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::UnsignedInt::body()
{
    return test<unsigned int>("9", 9u);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::UnsignedLong::body()
{
    return test<unsigned long>("44", 44ul);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::UnsignedLongLong::body()
{
    return test<unsigned long long>("12", 12ull);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::FromString::UnsignedShort::body()
{
    return test<unsigned short>("13", 13);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::String::body()
{
    return test<std::string>("1", "1");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::Char::body()
{
    return test<char>('a', "a");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::Double::body()
{
    return test<double>(14.333, "14.333");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::Float::body()
{
    return test<float>(13.2f, "13.2");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::Int::body()
{
    return test<int>(4, "4");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::Long::body()
{
    return test<long>(234, "234");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::LongDouble::body()
{
    return test<long double>(987.4l, "987.4");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::LongLong::body()
{
    return test<long long>(10000, "10000");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::Short::body()
{
    return test<short>(-111, "-111");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::UnsignedChar::body()
{
    return test<unsigned char>('9', "9");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::UnsignedInt::body()
{
    return test<unsigned int>(56791, "56791");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::UnsignedLong::body()
{
    return test<unsigned long>(99999, "99999");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::UnsignedLongLong::body()
{
    return test<unsigned long long>(11223344, "11223344");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::ToString::UnsignedShort::body()
{
    return test<unsigned short>(7766, "7766");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::String::body()
{
    return test<std::string>("abcd", "abcd");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::Char::body()
{
    return test<char>("a", 'a');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::Double::body()
{
    return test<double>("2.0", 2.0);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::Float::body()
{
    return test<float>("2.0", 2.0f);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::Int::body()
{
    return test<int>("3", 3);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::Long::body()
{
    return test<long>("4", 4);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::LongDouble::body()
{
    return test<long double>("5.0", 5.0l);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::LongLong::body()
{
    return test<long long>("6", 6ll);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::Short::body()
{
    return test<short>("7", 7);
}

//=============================================================================================
Test::Result
Configuration::SimpleParameter_test::OperatorStreamExtraction::UnsignedChar::body()
{
    return test<unsigned char>("x", 'x');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamExtraction::UnsignedInt::body()
{
    return test<unsigned int>("9", 9u);
}

//=============================================================================================
Test::Result
Configuration::SimpleParameter_test::OperatorStreamExtraction::UnsignedLong::body()
{
    return test<unsigned long>("44", 44ul);
}

//=============================================================================================
Test::Result
Configuration::SimpleParameter_test::OperatorStreamExtraction::UnsignedLongLong::body()
{
    return test<unsigned long long>("12", 12ull);
}

//=============================================================================================
Test::Result
Configuration::SimpleParameter_test::OperatorStreamExtraction::UnsignedShort::body()
{
    return test<unsigned short>("13", 13);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::String::body()
{
    return test<std::string>("1", "1");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::Char::body()
{
    return test<char>('a', "a");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::Double::body()
{
    return test<double>(14.333, "14.333");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::Float::body()
{
    return test<float>(13.2f, "13.2");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::Int::body()
{
    return test<int>(4, "4");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::Long::body()
{
    return test<long>(234, "234");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::LongDouble::body()
{
    return test<long double>(987.4l, "987.4");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::LongLong::body()
{
    return test<long long>(10000, "10000");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::Short::body()
{
    return test<short>(-111, "-111");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::UnsignedChar::body()
{
    return test<unsigned char>('9', "9");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::UnsignedInt::body()
{
    return test<unsigned int>(56791, "56791");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorStreamInsertion::UnsignedLong::body()
{
    return test<unsigned long>(99999, "99999");
}

//=============================================================================================
Test::Result
Configuration::SimpleParameter_test::OperatorStreamInsertion::UnsignedLongLong::body()
{
    return test<unsigned long long>(11223344, "11223344");
}

//=============================================================================================
Test::Result
Configuration::SimpleParameter_test::OperatorStreamInsertion::UnsignedShort::body()
{
    return test<unsigned short>(7766, "7766");
}

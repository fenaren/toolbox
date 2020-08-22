#include <iostream>
#include <string>

#include "ConfigurationSimpleParameter_test.hpp"

#include "ConfigurationSimpleParameter.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration::SimpleParameter_test);

//=============================================================================================
void Configuration::SimpleParameter_test::addTestCases()
{
    ADD_TEST_CASE(Generic);
    ADD_TEST_CASE(List);
}

//=============================================================================================
void Configuration::SimpleParameter_test::List::addTestCases()
{
    ADD_TEST_CASE(FromString);
    ADD_TEST_CASE(ToString);
}

//=============================================================================================
void Configuration::SimpleParameter_test::List::FromString::addTestCases()
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
void Configuration::SimpleParameter_test::List::ToString::addTestCases()
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
Test::Result Configuration::SimpleParameter_test::Generic::body()
{
    // Just try to instantiate all the supported types. SimpleParameter doesn't add any new
    // code to test in the usual way.

    SimpleParameter<char> temp1;
    SimpleParameter<double> temp2;
    SimpleParameter<float> temp3;
    SimpleParameter<int> temp4;
    SimpleParameter<long> temp5;
    SimpleParameter<long double> temp6;
    SimpleParameter<long long> temp7;
    SimpleParameter<short> temp8;
    SimpleParameter<unsigned char> temp9;
    SimpleParameter<unsigned int> temp10;
    SimpleParameter<unsigned long> temp11;
    SimpleParameter<unsigned long long> temp12;
    SimpleParameter<unsigned short> temp13;
    SimpleParameter<std::string> temp14;

    return Test::PASSED;
}

//=============================================================================================
template <class T> Test::Result Configuration::SimpleParameter_test::List::FromString::test(
    const std::string& initial_value, const std::list<T>& should_equal)
{
    SimpleParameter<std::list<T> > temp;
    temp.fromString(initial_value);

    std::list<T> temp_value;
    temp.getValue(temp_value);

    MUST_BE_TRUE(temp_value == should_equal);

    return Test::PASSED;
}

//=============================================================================================
template <class T> Test::Result Configuration::SimpleParameter_test::List::ToString::test(
    const std::list<T>& initial_value, const std::string& should_equal)
{
    SimpleParameter<std::list<T> > temp(initial_value);

    std::string temp_string;
    temp.toString(temp_string);
    std::cout << temp_string << "\n";

    MUST_BE_TRUE(temp_string == should_equal);

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::String::body()
{
    // The space is in the first string on purpose
    return test<std::string>("a b c  d", std::list<std::string>({"a", "b", "c", "d"}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::Char::body()
{
    return test<char>("a b c d", std::list<char>({'a', 'b', 'c', 'd'}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::Double::body()
{
    return test<double>("2.0 3 4.4 5.5", std::list<double>({2.0, 3, 4.4, 5.5}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::Float::body()
{
    return test<float>("1 2.1 3.1", std::list<float>({1.0f, 2.1f, 3.1f}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::Int::body()
{
    return test<int>("3 -33 333 -3333", std::list<int>({3, -33, 333, -3333}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::Long::body()
{
    return test<long>("4 -44 444 -4444", std::list<long>({4l, -44l, 444l, -4444l}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::LongDouble::body()
{
    return test<long double>("5.0 7 9 11 13",
                             std::list<long double>({5.0l, 7.0l, 9.0l, 11.0l, 13.0l}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::LongLong::body()
{
    return test<long long>("-5 -3 -1 1 3 5",
                           std::list<long long>({-5ll, -3ll, -1ll, 1ll, 3ll, 5ll}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::Short::body()
{
    return test<short>("-1 -2 -3 -4", std::list<short>({-1, -2, -3, -4}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::UnsignedChar::body()
{
    return test<unsigned char>("x y z", std::list<unsigned char>({'x', 'y', 'z'}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::UnsignedInt::body()
{
    return test<unsigned int>("9 12  15", std::list<unsigned int>({9, 12, 15}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::UnsignedLong::body()
{
    return test<unsigned long>("44 45 46 47 48",
                               std::list<unsigned long>({44ul, 45ul, 46ul, 47ul, 48ul}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::UnsignedLongLong::body()
{
    return test<unsigned long long>("12 11 10",
                                    std::list<unsigned long long>({12ull, 11ull, 10ull}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::FromString::UnsignedShort::body()
{
    return test<unsigned short>("13 1     2    3", std::list<unsigned short>({13, 1, 2, 3}));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::String::body()
{
    return test<std::string>(std::list<std::string>({"123", ".45", "6"}),
                             "123 .45 6");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::Char::body()
{
    return test<char>(std::list<char>({'a', 'b'}), "a b");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::Double::body()
{
    return test<double>(std::list<double>({}), "");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::Float::body()
{
    return test<float>(std::list<float>({1.5f, 2.5f, 3.5f, 4.5f}), "1.5 2.5 3.5 4.5");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::Int::body()
{
    return test<int>(std::list<int>({1, 2, 3, 4, 5}), "1 2 3 4 5");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::Long::body()
{
    return test<long>(std::list<long>({9l, 99l, 999l}), "9 99 999");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::LongDouble::body()
{
    return test<long double>(std::list<long double>({30.2l, 50.2l}), "30.2 50.2");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::LongLong::body()
{
    return test<long long>(std::list<long long>({1ll, 2ll, 3ll, 4ll}), "1 2 3 4");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::Short::body()
{
    return test<short>(std::list<short>({}), "");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::UnsignedChar::body()
{
    return test<unsigned char>(std::list<unsigned char>({'h', 'i', 'j'}), "h i j");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::UnsignedInt::body()
{
    return test<unsigned int>(std::list<unsigned int>({5, 10, 15}), "5 10 15");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::UnsignedLong::body()
{
    return test<unsigned long>(std::list<unsigned long>({4ul}), "4");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::UnsignedLongLong::body()
{
    return test<unsigned long long>(std::list<unsigned long long>({3ull}), "3");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::List::ToString::UnsignedShort::body()
{
    return test<unsigned short>(std::list<unsigned short>({9, 8, 7}), "9 8 7");
}

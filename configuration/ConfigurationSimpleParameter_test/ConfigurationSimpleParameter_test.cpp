#include <string>

#include "ConfigurationSimpleParameter_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ConfigurationSimpleParameter.hpp"

TEST_PROGRAM_MAIN(Configuration::SimpleParameter_test);

//=============================================================================================
void Configuration::SimpleParameter_test::addTestCases()
{
    ADD_TEST_CASE(SetValue);

    // Relational operators
    ADD_TEST_CASE(OperatorLessThan);
    ADD_TEST_CASE(OperatorGreaterThan);
    ADD_TEST_CASE(OperatorLessThanOrEqualTo);
    ADD_TEST_CASE(OperatorGreaterThanOrEqualTo);
    ADD_TEST_CASE(OperatorEquality);
    ADD_TEST_CASE(OperatorNotEqual);
    ADD_TEST_CASE(FromString);
    ADD_TEST_CASE(ToString);
}

//=============================================================================================
void Configuration::SimpleParameter_test::SetValue::addTestCases()
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
void Configuration::SimpleParameter_test::OperatorLessThan::addTestCases()
{
    ADD_TEST_CASE(StringConstCharP);
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
void Configuration::SimpleParameter_test::OperatorGreaterThan::addTestCases()
{
    ADD_TEST_CASE(StringConstCharP);
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
void Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::addTestCases()
{
    ADD_TEST_CASE(StringConstCharP);
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
void Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::addTestCases()
{
    ADD_TEST_CASE(StringConstCharP);
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
void Configuration::SimpleParameter_test::OperatorEquality::addTestCases()
{
    ADD_TEST_CASE(StringConstCharP);
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
void Configuration::SimpleParameter_test::OperatorNotEqual::addTestCases()
{
    ADD_TEST_CASE(StringConstCharP);
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
template <class T> Test::Result Configuration::SimpleParameter_test::SetValue::test(
    const T& initial_value,
    const T& set_value)
{
    SimpleParameter<T> configuration_value(initial_value);

    // Arguments are not set by default, even when given a default value.
    MUST_BE_TRUE(!configuration_value.isSet());

    configuration_value.setValue(set_value);

    // Now we should be set.
    MUST_BE_TRUE(configuration_value.isSet());

    // Get the value after the update and compare to what we expected.
    T retrieved_value;
    configuration_value.getValue(retrieved_value);
    MUST_BE_TRUE(set_value == retrieved_value);

    return Test::PASSED;
}

//=============================================================================================
template <class T>
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::test(const T& smaller,
                                                                   const T& bigger)
{
    SimpleParameter<T> arg_smaller(smaller);
    SimpleParameter<T> arg_bigger(bigger);

    // SimpleParameter<T> vs. SimpleParameter<T>
    MUST_BE_TRUE(arg_smaller < arg_bigger);
    MUST_BE_TRUE(!(arg_bigger < arg_smaller));
    MUST_BE_TRUE(!(arg_smaller < arg_smaller));

    // SimpleParameter<T> vs. const T
    MUST_BE_TRUE(arg_smaller < bigger);
    MUST_BE_TRUE(!(bigger < arg_smaller));
    MUST_BE_TRUE(!(arg_smaller < arg_smaller));

    // const T vs. SimpleParameter<T>
    MUST_BE_TRUE(smaller < arg_bigger);
    MUST_BE_TRUE(!(arg_bigger < smaller));
    MUST_BE_TRUE(!(smaller < smaller));

    return Test::PASSED;
}

//=============================================================================================
template <class T>
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::test(const T& smaller,
                                                                      const T& bigger)
{
    SimpleParameter<T> arg_smaller(smaller);
    SimpleParameter<T> arg_bigger(bigger);

    // SimpleParameter<T> vs. SimpleParameter<T>
    MUST_BE_TRUE(arg_bigger > arg_smaller);
    MUST_BE_TRUE(!(arg_smaller > arg_bigger));
    MUST_BE_TRUE(!(arg_smaller > arg_smaller));

    // SimpleParameter<T> vs. const T
    MUST_BE_TRUE(bigger > arg_smaller);
    MUST_BE_TRUE(!(arg_smaller > bigger));
    MUST_BE_TRUE(!(arg_smaller > arg_smaller));

    // const T vs. SimpleParameter<T>
    MUST_BE_TRUE(arg_bigger > smaller);
    MUST_BE_TRUE(!(smaller > arg_bigger));
    MUST_BE_TRUE(!(smaller > smaller));

    return Test::PASSED;
}

//=============================================================================================
template <class T>
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::test(const T& smaller,
                                                                            const T& bigger)
{
    SimpleParameter<T> arg_smaller(smaller);
    SimpleParameter<T> arg_bigger(bigger);

    // SimpleParameter<T> vs. SimpleParameter<T>
    MUST_BE_TRUE(arg_smaller <= arg_bigger);
    MUST_BE_TRUE(!(arg_bigger <= arg_smaller));
    MUST_BE_TRUE(arg_smaller <= arg_smaller);

    // SimpleParameter<T> vs. const T
    MUST_BE_TRUE(arg_smaller <= bigger);
    MUST_BE_TRUE(!(bigger <= arg_smaller));
    MUST_BE_TRUE(arg_smaller <= arg_smaller);

    // const T vs. SimpleParameter<T>
    MUST_BE_TRUE(smaller <= arg_bigger);
    MUST_BE_TRUE(!(arg_bigger <= smaller));
    MUST_BE_TRUE(smaller <= smaller);

    return Test::PASSED;
}

//=============================================================================================
template <class T> Test::Result
Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::test(const T& smaller,
                                                                  const T& bigger)
{
    SimpleParameter<T> arg_smaller(smaller);
    SimpleParameter<T> arg_bigger(bigger);

    // SimpleParameter<T> vs. SimpleParameter<T>
    MUST_BE_TRUE(arg_bigger >= arg_smaller);
    MUST_BE_TRUE(!(arg_smaller >= arg_bigger));
    MUST_BE_TRUE(arg_smaller >= arg_smaller);

    // SimpleParameter<T> vs. const T
    MUST_BE_TRUE(bigger >= arg_smaller);
    MUST_BE_TRUE(!(arg_smaller >= bigger));
    MUST_BE_TRUE(arg_smaller >= arg_smaller);

    // const T vs. SimpleParameter<T>
    MUST_BE_TRUE(arg_bigger >= smaller);
    MUST_BE_TRUE(!(smaller >= arg_bigger));
    MUST_BE_TRUE(smaller >= smaller);

    return Test::PASSED;
}

//=============================================================================================
template <class T> Test::Result Configuration::SimpleParameter_test::OperatorEquality::test(
    const T& smaller, const T& bigger)
{
    SimpleParameter<T> arg_smaller(smaller);
    SimpleParameter<T> arg_bigger(bigger);

    // SimpleParameter<T> vs. SimpleParameter<T>
    MUST_BE_TRUE(arg_smaller == arg_smaller);
    MUST_BE_TRUE(!(arg_smaller == arg_bigger));

    // SimpleParameter<T> vs. const T
    MUST_BE_TRUE(arg_smaller == arg_smaller);
    MUST_BE_TRUE(!(arg_smaller == bigger));

    // const T vs. SimpleParameter<T>
    MUST_BE_TRUE(smaller == smaller);
    MUST_BE_TRUE(!(smaller == arg_bigger));

    return Test::PASSED;
}

//=============================================================================================
template <class T> Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::test(
    const T& smaller, const T& bigger)
{
    SimpleParameter<T> arg_smaller(smaller);
    SimpleParameter<T> arg_bigger(bigger);

    // SimpleParameter<T> vs. SimpleParameter<T>
    MUST_BE_TRUE(arg_smaller != arg_bigger);
    MUST_BE_TRUE(!(arg_smaller != arg_smaller));

    // SimpleParameter<T> vs. const T
    MUST_BE_TRUE(arg_smaller != bigger);
    MUST_BE_TRUE(!(arg_smaller != arg_smaller));

    // const T vs. SimpleParameter<T>
    MUST_BE_TRUE(smaller != arg_bigger);
    MUST_BE_TRUE(!(smaller != smaller));

    return Test::PASSED;
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
Test::Result Configuration::SimpleParameter_test::SetValue::String::body()
{
    return test<std::string>("", "1234");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::Char::body()
{
    return test<char>(0, '1');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::Double::body()
{
    return test<double>(0, 111.0);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::Float::body()
{
    return test<float>(0, 111.0f);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::Int::body()
{
    return test<int>(0, 111);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::Long::body()
{
    return test<long>(0, 111L);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::LongDouble::body()
{
    return test<long double>(0, 111.0L);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::LongLong::body()
{
    return test<long long>(0, 111LL);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::Short::body()
{
    return test<short>(0, static_cast<short>(111));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::UnsignedChar::body()
{
    return test<unsigned char>(0, static_cast<unsigned char>('1'));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::UnsignedInt::body()
{
    return test<unsigned int>(0, 111U);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::UnsignedLong::body()
{
    return test<unsigned long>(0, 111);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 111ULL);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::SetValue::UnsignedShort::body()
{
    return test<unsigned short>(0, static_cast<unsigned short>(111));
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    SimpleParameter<std::string> smaller_arg(smaller);
    SimpleParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(smaller < bigger_arg);
    MUST_BE_TRUE(smaller_arg < bigger);
    MUST_BE_TRUE(!(smaller_arg < smaller));

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThan::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    SimpleParameter<std::string> smaller_arg(smaller);
    SimpleParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger_arg > smaller);
    MUST_BE_TRUE(bigger > smaller_arg);
    MUST_BE_TRUE(!(bigger > bigger_arg));

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThan::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    SimpleParameter<std::string> smaller_arg(smaller);
    SimpleParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(smaller <= bigger_arg);
    MUST_BE_TRUE(smaller_arg <= bigger);
    MUST_BE_TRUE(smaller_arg <= smaller);

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorLessThanOrEqualTo::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//=============================================================================================
Test::Result
Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    SimpleParameter<std::string> smaller_arg(smaller);
    SimpleParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger >= smaller_arg);
    MUST_BE_TRUE(bigger_arg  >= smaller);
    MUST_BE_TRUE(smaller_arg >= smaller);

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result
Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorGreaterThanOrEqualTo::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    SimpleParameter<std::string> smaller_arg(smaller);
    SimpleParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger == bigger_arg);
    MUST_BE_TRUE(bigger_arg == bigger);

    MUST_BE_TRUE(!(bigger == smaller_arg));
    MUST_BE_TRUE(!(bigger_arg == smaller));

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorEquality::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    SimpleParameter<std::string> smaller_arg(smaller);
    SimpleParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger != smaller_arg);
    MUST_BE_TRUE(bigger_arg != smaller);

    MUST_BE_TRUE(!(bigger != bigger_arg));
    MUST_BE_TRUE(!(bigger_arg != bigger));

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::SimpleParameter_test::OperatorNotEqual::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
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

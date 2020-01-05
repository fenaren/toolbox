#include <string>

#include "ArgumentValue_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ArgumentValue.hpp"

TEST_PROGRAM_MAIN(ArgumentValue_test);

//==============================================================================
void ArgumentValue_test::addTestCases()
{
    ADD_TEST_CASE(Update);

    // Relational operators
    ADD_TEST_CASE(OperatorLessThan);
    ADD_TEST_CASE(OperatorGreaterThan);
    ADD_TEST_CASE(OperatorLessThanOrEqualTo);
    ADD_TEST_CASE(OperatorGreaterThanOrEqualTo);
    ADD_TEST_CASE(OperatorEquality);
    ADD_TEST_CASE(OperatorNotEqual);
}

//==============================================================================
void ArgumentValue_test::Update::addTestCases()
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

//==============================================================================
void ArgumentValue_test::OperatorLessThan::addTestCases()
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

//==============================================================================
void ArgumentValue_test::OperatorGreaterThan::addTestCases()
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

//==============================================================================
void ArgumentValue_test::OperatorLessThanOrEqualTo::addTestCases()
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

//==============================================================================
void ArgumentValue_test::OperatorGreaterThanOrEqualTo::addTestCases()
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

//==============================================================================
void ArgumentValue_test::OperatorEquality::addTestCases()
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

//==============================================================================
void ArgumentValue_test::OperatorNotEqual::addTestCases()
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

//==============================================================================
template <class T>
Test::Result ArgumentValue_test::Update::test(const T&           default_value,
                                              const std::string& update_value,
                                              const T&           expected_value)
{
    ArgumentValue<T> argument_value(default_value);

    // Arguments are not set by default, even when given a default value.
    MUST_BE_TRUE(!argument_value.isSet());

    argument_value.update(update_value);

    // Now we should be set.
    MUST_BE_TRUE(argument_value.isSet());

    // Get the value after the update and compare to what we expected.
    T set_value;
    argument_value.getValue(set_value);
    MUST_BE_TRUE(set_value == expected_value);

    return Test::PASSED;
}

//==============================================================================
template <class T>
Test::Result ArgumentValue_test::OperatorLessThan::test(const T& smaller,
                                                        const T& bigger)
{
    ArgumentValue<T> arg_smaller(smaller);
    ArgumentValue<T> arg_bigger(bigger);

    // ArgumentValue<T> vs. ArgumentValue<T>
    MUST_BE_TRUE(arg_smaller < arg_bigger);
    MUST_BE_TRUE(!(arg_bigger < arg_smaller));
    MUST_BE_TRUE(!(arg_smaller < arg_smaller));

    // ArgumentValue<T> vs. const T
    MUST_BE_TRUE(arg_smaller < bigger);
    MUST_BE_TRUE(!(bigger < arg_smaller));
    MUST_BE_TRUE(!(arg_smaller < arg_smaller));

    // const T vs. ArgumentValue<T>
    MUST_BE_TRUE(smaller < arg_bigger);
    MUST_BE_TRUE(!(arg_bigger < smaller));
    MUST_BE_TRUE(!(smaller < smaller));

    return Test::PASSED;
}

//==============================================================================
template <class T>
Test::Result ArgumentValue_test::OperatorGreaterThan::test(const T& smaller,
                                                           const T& bigger)
{
    ArgumentValue<T> arg_smaller(smaller);
    ArgumentValue<T> arg_bigger(bigger);

    // ArgumentValue<T> vs. ArgumentValue<T>
    MUST_BE_TRUE(arg_bigger > arg_smaller);
    MUST_BE_TRUE(!(arg_smaller > arg_bigger));
    MUST_BE_TRUE(!(arg_smaller > arg_smaller));

    // ArgumentValue<T> vs. const T
    MUST_BE_TRUE(bigger > arg_smaller);
    MUST_BE_TRUE(!(arg_smaller > bigger));
    MUST_BE_TRUE(!(arg_smaller > arg_smaller));

    // const T vs. ArgumentValue<T>
    MUST_BE_TRUE(arg_bigger > smaller);
    MUST_BE_TRUE(!(smaller > arg_bigger));
    MUST_BE_TRUE(!(smaller > smaller));

    return Test::PASSED;
}

//==============================================================================
template <class T> Test::Result
ArgumentValue_test::OperatorLessThanOrEqualTo::test(const T& smaller,
                                                    const T& bigger)
{
    ArgumentValue<T> arg_smaller(smaller);
    ArgumentValue<T> arg_bigger(bigger);

    // ArgumentValue<T> vs. ArgumentValue<T>
    MUST_BE_TRUE(arg_smaller <= arg_bigger);
    MUST_BE_TRUE(!(arg_bigger <= arg_smaller));
    MUST_BE_TRUE(arg_smaller <= arg_smaller);

    // ArgumentValue<T> vs. const T
    MUST_BE_TRUE(arg_smaller <= bigger);
    MUST_BE_TRUE(!(bigger <= arg_smaller));
    MUST_BE_TRUE(arg_smaller <= arg_smaller);

    // const T vs. ArgumentValue<T>
    MUST_BE_TRUE(smaller <= arg_bigger);
    MUST_BE_TRUE(!(arg_bigger <= smaller));
    MUST_BE_TRUE(smaller <= smaller);

    return Test::PASSED;
}

//==============================================================================
template <class T> Test::Result
ArgumentValue_test::OperatorGreaterThanOrEqualTo::test(const T& smaller,
                                                       const T& bigger)
{
    ArgumentValue<T> arg_smaller(smaller);
    ArgumentValue<T> arg_bigger(bigger);

    // ArgumentValue<T> vs. ArgumentValue<T>
    MUST_BE_TRUE(arg_bigger >= arg_smaller);
    MUST_BE_TRUE(!(arg_smaller >= arg_bigger));
    MUST_BE_TRUE(arg_smaller >= arg_smaller);

    // ArgumentValue<T> vs. const T
    MUST_BE_TRUE(bigger >= arg_smaller);
    MUST_BE_TRUE(!(arg_smaller >= bigger));
    MUST_BE_TRUE(arg_smaller >= arg_smaller);

    // const T vs. ArgumentValue<T>
    MUST_BE_TRUE(arg_bigger >= smaller);
    MUST_BE_TRUE(!(smaller >= arg_bigger));
    MUST_BE_TRUE(smaller >= smaller);

    return Test::PASSED;
}

//==============================================================================
template <class T> Test::Result ArgumentValue_test::OperatorEquality::test(
    const T& smaller, const T& bigger)
{
    ArgumentValue<T> arg_smaller(smaller);
    ArgumentValue<T> arg_bigger(bigger);

    // ArgumentValue<T> vs. ArgumentValue<T>
    MUST_BE_TRUE(arg_smaller == arg_smaller);
    MUST_BE_TRUE(!(arg_smaller == arg_bigger));

    // ArgumentValue<T> vs. const T
    MUST_BE_TRUE(arg_smaller == arg_smaller);
    MUST_BE_TRUE(!(arg_smaller == bigger));

    // const T vs. ArgumentValue<T>
    MUST_BE_TRUE(smaller == smaller);
    MUST_BE_TRUE(!(smaller == arg_bigger));

    return Test::PASSED;
}

//==============================================================================
template <class T> Test::Result ArgumentValue_test::OperatorNotEqual::test(
    const T& smaller, const T& bigger)
{
    ArgumentValue<T> arg_smaller(smaller);
    ArgumentValue<T> arg_bigger(bigger);

    // ArgumentValue<T> vs. ArgumentValue<T>
    MUST_BE_TRUE(arg_smaller != arg_bigger);
    MUST_BE_TRUE(!(arg_smaller != arg_smaller));

    // ArgumentValue<T> vs. const T
    MUST_BE_TRUE(arg_smaller != bigger);
    MUST_BE_TRUE(!(arg_smaller != arg_smaller));

    // const T vs. ArgumentValue<T>
    MUST_BE_TRUE(smaller != arg_bigger);
    MUST_BE_TRUE(!(smaller != smaller));

    return Test::PASSED;
}

//==============================================================================
// UPDATE
//==============================================================================

Test::Result ArgumentValue_test::Update::String::body()
{
    return test<std::string>("", "1234", "1234");
}

Test::Result ArgumentValue_test::Update::Char::body()
{
    return test<char>(0, "111", '1');
}

Test::Result ArgumentValue_test::Update::Double::body()
{
    return test<double>(0, "111", 111.0);
}

Test::Result ArgumentValue_test::Update::Float::body()
{
    return test<float>(0, "111", 111.0f);
}

Test::Result ArgumentValue_test::Update::Int::body()
{
    return test<int>(0, "111", 111);
}

Test::Result ArgumentValue_test::Update::Long::body()
{
    return test<long>(0, "111", 111L);
}

Test::Result ArgumentValue_test::Update::LongDouble::body()
{
    return test<long double>(0, "111", 111.0L);
}

Test::Result ArgumentValue_test::Update::LongLong::body()
{
    return test<long long>(0, "111", 111LL);
}

Test::Result ArgumentValue_test::Update::Short::body()
{
    return test<short>(0, "111", static_cast<short>(111));
}

Test::Result ArgumentValue_test::Update::UnsignedChar::body()
{
    return test<unsigned char>(0, "111", static_cast<unsigned char>('1'));
}

Test::Result ArgumentValue_test::Update::UnsignedInt::body()
{
    return test<unsigned int>(0, "111", 111U);
}

Test::Result ArgumentValue_test::Update::UnsignedLong::body()
{
    return test<unsigned long>(0, "111", 111);
}

Test::Result ArgumentValue_test::Update::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, "111", 111ULL);
}

Test::Result ArgumentValue_test::Update::UnsignedShort::body()
{
    return test<unsigned short>(0, "111", static_cast<unsigned short>(111));
}

//==============================================================================
// OPERATOR LESS THAN
//==============================================================================

Test::Result ArgumentValue_test::OperatorLessThan::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    ArgumentValue<std::string> smaller_arg(smaller);
    ArgumentValue<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(smaller     < bigger_arg);
    MUST_BE_TRUE(smaller_arg < bigger);
    MUST_BE_TRUE(!(smaller_arg < smaller));

    return Test::PASSED;
}

Test::Result ArgumentValue_test::OperatorLessThan::String::body()
{
    return test<std::string>("abcd", "efgh");
}

Test::Result ArgumentValue_test::OperatorLessThan::Char::body()
{
    return test<char>('a', 'b');
}

Test::Result ArgumentValue_test::OperatorLessThan::Double::body()
{
    return test<double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::Float::body()
{
    return test<float>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::Int::body()
{
    return test<int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::Long::body()
{
    return test<long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::LongDouble::body()
{
    return test<long double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::LongLong::body()
{
    return test<long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::Short::body()
{
    return test<short>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThan::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//==============================================================================
// OPERATOR GREATER THAN
//==============================================================================

Test::Result ArgumentValue_test::OperatorGreaterThan::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    ArgumentValue<std::string> smaller_arg(smaller);
    ArgumentValue<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger_arg > smaller);
    MUST_BE_TRUE(bigger     > smaller_arg);
    MUST_BE_TRUE(!(bigger     > bigger_arg));

    return Test::PASSED;
}

Test::Result ArgumentValue_test::OperatorGreaterThan::String::body()
{
    return test<std::string>("abcd", "efgh");
}

Test::Result ArgumentValue_test::OperatorGreaterThan::Char::body()
{
    return test<char>('a', 'b');
}

Test::Result ArgumentValue_test::OperatorGreaterThan::Double::body()
{
    return test<double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::Float::body()
{
    return test<float>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::Int::body()
{
    return test<int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::Long::body()
{
    return test<long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::LongDouble::body()
{
    return test<long double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::LongLong::body()
{
    return test<long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::Short::body()
{
    return test<short>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThan::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//==============================================================================
// OPERATOR LESS THAN OR EQUAL TO
//==============================================================================

Test::Result
ArgumentValue_test::OperatorLessThanOrEqualTo::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    ArgumentValue<std::string> smaller_arg(smaller);
    ArgumentValue<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(smaller     <= bigger_arg);
    MUST_BE_TRUE(smaller_arg <= bigger);
    MUST_BE_TRUE(smaller_arg <= smaller);

    return Test::PASSED;
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::String::body()
{
    return test<std::string>("abcd", "efgh");
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::Char::body()
{
    return test<char>('a', 'b');
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::Double::body()
{
    return test<double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::Float::body()
{
    return test<float>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::Int::body()
{
    return test<int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::Long::body()
{
    return test<long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::LongDouble::body()
{
    return test<long double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::LongLong::body()
{
    return test<long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::Short::body()
{
    return test<short>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorLessThanOrEqualTo::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//==============================================================================
// OPERATOR GREATER THAN OR EQUAL TO
//==============================================================================

Test::Result
ArgumentValue_test::OperatorGreaterThanOrEqualTo::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    ArgumentValue<std::string> smaller_arg(smaller);
    ArgumentValue<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger      >= smaller_arg);
    MUST_BE_TRUE(bigger_arg  >= smaller);
    MUST_BE_TRUE(smaller_arg >= smaller);

    return Test::PASSED;
}

Test::Result ArgumentValue_test::OperatorGreaterThanOrEqualTo::String::body()
{
    return test<std::string>("abcd", "efgh");
}

Test::Result ArgumentValue_test::OperatorGreaterThanOrEqualTo::Char::body()
{
    return test<char>('a', 'b');
}

Test::Result ArgumentValue_test::OperatorGreaterThanOrEqualTo::Double::body()
{
    return test<double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThanOrEqualTo::Float::body()
{
    return test<float>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThanOrEqualTo::Int::body()
{
    return test<int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThanOrEqualTo::Long::body()
{
    return test<long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThanOrEqualTo::LongDouble::body()
{
    return test<long double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThanOrEqualTo::LongLong::body()
{
    return test<long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorGreaterThanOrEqualTo::Short::body()
{
    return test<short>(0, 1);
}

Test::Result
ArgumentValue_test::OperatorGreaterThanOrEqualTo::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

Test::Result
ArgumentValue_test::OperatorGreaterThanOrEqualTo::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

Test::Result
ArgumentValue_test::OperatorGreaterThanOrEqualTo::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

Test::Result
ArgumentValue_test::OperatorGreaterThanOrEqualTo::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

Test::Result
ArgumentValue_test::OperatorGreaterThanOrEqualTo::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//==============================================================================
// OPERATOR EQUALITY
//==============================================================================

Test::Result ArgumentValue_test::OperatorEquality::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    ArgumentValue<std::string> smaller_arg(smaller);
    ArgumentValue<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger      == bigger_arg);
    MUST_BE_TRUE(bigger_arg  == bigger);

    MUST_BE_TRUE(!(bigger == smaller_arg));
    MUST_BE_TRUE(!(bigger_arg == smaller));

    return Test::PASSED;
}

Test::Result ArgumentValue_test::OperatorEquality::String::body()
{
    return test<std::string>("abcd", "efgh");
}

Test::Result ArgumentValue_test::OperatorEquality::Char::body()
{
    return test<char>('a', 'b');
}

Test::Result ArgumentValue_test::OperatorEquality::Double::body()
{
    return test<double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::Float::body()
{
    return test<float>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::Int::body()
{
    return test<int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::Long::body()
{
    return test<long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::LongDouble::body()
{
    return test<long double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::LongLong::body()
{
    return test<long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::Short::body()
{
    return test<short>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorEquality::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//==============================================================================
// OPERATOR NOT EQUAL
//==============================================================================

Test::Result ArgumentValue_test::OperatorNotEqual::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    ArgumentValue<std::string> smaller_arg(smaller);
    ArgumentValue<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger     != smaller_arg);
    MUST_BE_TRUE(bigger_arg != smaller);

    MUST_BE_TRUE(!(bigger     != bigger_arg));
    MUST_BE_TRUE(!(bigger_arg != bigger));

    return Test::PASSED;
}

Test::Result ArgumentValue_test::OperatorNotEqual::String::body()
{
    return test<std::string>("abcd", "efgh");
}

Test::Result ArgumentValue_test::OperatorNotEqual::Char::body()
{
    return test<char>('a', 'b');
}

Test::Result ArgumentValue_test::OperatorNotEqual::Double::body()
{
    return test<double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::Float::body()
{
    return test<float>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::Int::body()
{
    return test<int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::Long::body()
{
    return test<long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::LongDouble::body()
{
    return test<long double>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::LongLong::body()
{
    return test<long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::Short::body()
{
    return test<short>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

Test::Result ArgumentValue_test::OperatorNotEqual::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

#include <list>
#include <string>

#include "ConfigurationListParameter_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ConfigurationListParameter.hpp"

TEST_PROGRAM_MAIN(Configuration::ListParameter_test);

namespace Configuration
{

    //==========================================================================
    void ListParameter_test::addTestCases()
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

    //==========================================================================
    void ListParameter_test::Update::addTestCases()
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

    //==========================================================================
    void ListParameter_test::OperatorLessThan::addTestCases()
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

    //==========================================================================
    void ListParameter_test::OperatorGreaterThan::addTestCases()
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

    //==========================================================================
    void ListParameter_test::OperatorLessThanOrEqualTo::addTestCases()
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

    //==========================================================================
    void ListParameter_test::OperatorGreaterThanOrEqualTo::addTestCases()
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

    //==========================================================================
    void ListParameter_test::OperatorEquality::addTestCases()
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

    //==========================================================================
    void ListParameter_test::OperatorNotEqual::addTestCases()
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

    //==========================================================================
    template <class T> Test::Result
    ListParameter_test::Update::test(const std::list<T>& default_value,
                                     const std::string&  update_value,
                                     const std::list<T>& expected_value)
    {
        ListParameter<T> configuration_value(default_value);

        // Arguments are not set by default, even when given a default value.
        MUST_BE_TRUE(!configuration_value.isSet());

        configuration_value.updateValue(update_value);

        // Now we should be set.
        MUST_BE_TRUE(configuration_value.isSet());

        // Get the value after the update and compare to what we expected.
        std::list<T> set_value;
        configuration_value.getValue(set_value);
        MUST_BE_TRUE(set_value == expected_value);

        return Test::PASSED;
    }

    //==========================================================================
    template <class T> Test::Result
    ListParameter_test::OperatorLessThan::test(const std::list<T>& smaller,
                                               const std::list<T>& bigger)
    {
        ListParameter<T> arg_smaller(smaller);
        ListParameter<T> arg_bigger(bigger);

        // ListParameter<T> vs. ListParameter<T>
        MUST_BE_TRUE(arg_smaller < arg_bigger);
        MUST_BE_TRUE(!(arg_bigger < arg_smaller));
        MUST_BE_TRUE(!(arg_smaller < arg_smaller));

        // ListParameter<T> vs. const T
        MUST_BE_TRUE(arg_smaller < bigger);
        MUST_BE_TRUE(!(bigger < arg_smaller));
        MUST_BE_TRUE(!(arg_smaller < arg_smaller));

        // const T vs. ListParameter<T>
        MUST_BE_TRUE(smaller < arg_bigger);
        MUST_BE_TRUE(!(arg_bigger < smaller));
        MUST_BE_TRUE(!(smaller < smaller));

        return Test::PASSED;
    }

    //==========================================================================
    template <class T> Test::Result
    ListParameter_test::OperatorGreaterThan::test(const std::list<T>& smaller,
                                                  const std::list<T>& bigger)
    {
        ListParameter<T> arg_smaller(smaller);
        ListParameter<T> arg_bigger(bigger);

        // ListParameter<T> vs. ListParameter<T>
        MUST_BE_TRUE(arg_bigger > arg_smaller);
        MUST_BE_TRUE(!(arg_smaller > arg_bigger));
        MUST_BE_TRUE(!(arg_smaller > arg_smaller));

        // ListParameter<T> vs. const T
        MUST_BE_TRUE(bigger > arg_smaller);
        MUST_BE_TRUE(!(arg_smaller > bigger));
        MUST_BE_TRUE(!(arg_smaller > arg_smaller));

        // const T vs. ListParameter<T>
        MUST_BE_TRUE(arg_bigger > smaller);
        MUST_BE_TRUE(!(smaller > arg_bigger));
        MUST_BE_TRUE(!(smaller > smaller));

        return Test::PASSED;
    }

    //==========================================================================
    template <class T>
    Test::Result ListParameter_test::OperatorLessThanOrEqualTo::test(
        const std::list<T>& smaller, const std::list<T>& bigger)
    {
        ListParameter<T> arg_smaller(smaller);
        ListParameter<T> arg_bigger(bigger);

        // ListParameter<T> vs. ListParameter<T>
        MUST_BE_TRUE(arg_smaller <= arg_bigger);
        MUST_BE_TRUE(!(arg_bigger <= arg_smaller));
        MUST_BE_TRUE(arg_smaller <= arg_smaller);

        // ListParameter<T> vs. const T
        MUST_BE_TRUE(arg_smaller <= bigger);
        MUST_BE_TRUE(!(bigger <= arg_smaller));
        MUST_BE_TRUE(arg_smaller <= arg_smaller);

        // const T vs. ListParameter<T>
        MUST_BE_TRUE(smaller <= arg_bigger);
        MUST_BE_TRUE(!(arg_bigger <= smaller));
        MUST_BE_TRUE(smaller <= smaller);

        return Test::PASSED;
    }

    //==========================================================================
    template <class T> Test::Result
    ListParameter_test::OperatorGreaterThanOrEqualTo::test(
        const std::list<T>& smaller, const std::list<T>& bigger)
    {
        ListParameter<T> arg_smaller(smaller);
        ListParameter<T> arg_bigger(bigger);

        // ListParameter<T> vs. ListParameter<T>
        MUST_BE_TRUE(arg_bigger >= arg_smaller);
        MUST_BE_TRUE(!(arg_smaller >= arg_bigger));
        MUST_BE_TRUE(arg_smaller >= arg_smaller);

        // ListParameter<T> vs. const T
        MUST_BE_TRUE(bigger >= arg_smaller);
        MUST_BE_TRUE(!(arg_smaller >= bigger));
        MUST_BE_TRUE(arg_smaller >= arg_smaller);

        // const T vs. ListParameter<T>
        MUST_BE_TRUE(arg_bigger >= smaller);
        MUST_BE_TRUE(!(smaller >= arg_bigger));
        MUST_BE_TRUE(smaller >= smaller);

        return Test::PASSED;
    }

    //==========================================================================
    template <class T> Test::Result ListParameter_test::OperatorEquality::test(
        const std::list<T>& smaller, const std::list<T>& bigger)
    {
        ListParameter<T> arg_smaller(smaller);
        ListParameter<T> arg_bigger(bigger);

        // ListParameter<T> vs. ListParameter<T>
        MUST_BE_TRUE(arg_smaller == arg_smaller);
        MUST_BE_TRUE(!(arg_smaller == arg_bigger));

        // ListParameter<T> vs. const T
        MUST_BE_TRUE(arg_smaller == arg_smaller);
        MUST_BE_TRUE(!(arg_smaller == bigger));

        // const T vs. ListParameter<T>
        MUST_BE_TRUE(smaller == smaller);
        MUST_BE_TRUE(!(smaller == arg_bigger));

        return Test::PASSED;
    }

    //==========================================================================
    template <class T> Test::Result ListParameter_test::OperatorNotEqual::test(
        const std::list<T>& smaller, const std::list<T>& bigger)
    {
        ListParameter<T> arg_smaller(smaller);
        ListParameter<T> arg_bigger(bigger);

        // ListParameter<T> vs. ListParameter<T>
        MUST_BE_TRUE(arg_smaller != arg_bigger);
        MUST_BE_TRUE(!(arg_smaller != arg_smaller));

        // ListParameter<T> vs. const T
        MUST_BE_TRUE(arg_smaller != bigger);
        MUST_BE_TRUE(!(arg_smaller != arg_smaller));

        // const T vs. ListParameter<T>
        MUST_BE_TRUE(smaller != arg_bigger);
        MUST_BE_TRUE(!(smaller != smaller));

        return Test::PASSED;
    }

    //==========================================================================
    // UPDATE
    //==========================================================================

    Test::Result ListParameter_test::Update::String::body()
    {
        return test<std::string>({}, {"1234"}, {"1234"});
    }

    Test::Result ListParameter_test::Update::Char::body()
    {
        return test<char>({0}, {"111"}, {'1'});
    }

    Test::Result ListParameter_test::Update::Double::body()
    {
        return test<double>({0}, {"111"}, {111.0});
    }

    Test::Result ListParameter_test::Update::Float::body()
    {
        return test<float>({0}, {"111"}, {111.0f});
    }

    Test::Result ListParameter_test::Update::Int::body()
    {
        return test<int>({0}, {"111"}, {111});
    }

    Test::Result ListParameter_test::Update::Long::body()
    {
        return test<long>({0}, {"111"}, {111L});
    }

    Test::Result ListParameter_test::Update::LongDouble::body()
    {
        return test<long double>({0}, {"111"}, {111.0L});
    }

    Test::Result ListParameter_test::Update::LongLong::body()
    {
        return test<long long>({0}, {"111"}, {111LL});
    }

    Test::Result ListParameter_test::Update::Short::body()
    {
        return test<short>({0}, {"111"}, {static_cast<short>(111)});
    }

    Test::Result ListParameter_test::Update::UnsignedChar::body()
    {
        return test<unsigned char>(
            {0}, {"111"}, {static_cast<unsigned char>('1')});
    }

    Test::Result ListParameter_test::Update::UnsignedInt::body()
    {
        return test<unsigned int>({0}, {"111"}, {111U});
    }

    Test::Result ListParameter_test::Update::UnsignedLong::body()
    {
        return test<unsigned long>({0}, {"111"}, {111});
    }

    Test::Result ListParameter_test::Update::UnsignedLongLong::body()
    {
        return test<unsigned long long>({0}, {"111"}, {111ULL});
    }

    Test::Result ListParameter_test::Update::UnsignedShort::body()
    {
        return test<unsigned short>(
            {0}, {"111"}, {static_cast<unsigned short>(111)});
    }

    //==========================================================================
    // OPERATOR LESS THAN
    //==========================================================================

    Test::Result ListParameter_test::OperatorLessThan::String::body()
    {
        return test<std::string>({"abcd"}, {"efgh"});
    }

    Test::Result ListParameter_test::OperatorLessThan::Char::body()
    {
        return test<char>({'a'}, {'b'});
    }

    Test::Result ListParameter_test::OperatorLessThan::Double::body()
    {
        return test<double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::Float::body()
    {
        return test<float>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::Int::body()
    {
        return test<int>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::Long::body()
    {
        return test<long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::LongDouble::body()
    {
        return test<long double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::LongLong::body()
    {
        return test<long long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::Short::body()
    {
        return test<short>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::UnsignedChar::body()
    {
        return test<unsigned char>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::UnsignedInt::body()
    {
        return test<unsigned int>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::UnsignedLong::body()
    {
        return test<unsigned long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::UnsignedLongLong::body()
    {
        return test<unsigned long long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThan::UnsignedShort::body()
    {
        return test<unsigned short>({0}, {1});
    }

    //==========================================================================
    // OPERATOR GREATER THAN
    //==========================================================================

    Test::Result ListParameter_test::OperatorGreaterThan::String::body()
    {
        return test<std::string>({"abcd"}, {"efgh"});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::Char::body()
    {
        return test<char>({'a'}, {'b'});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::Double::body()
    {
        return test<double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::Float::body()
    {
        return test<float>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::Int::body()
    {
        return test<int>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::Long::body()
    {
        return test<long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::LongDouble::body()
    {
        return test<long double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::LongLong::body()
    {
        return test<long long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::Short::body()
    {
        return test<short>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::UnsignedChar::body()
    {
        return test<unsigned char>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::UnsignedInt::body()
    {
        return test<unsigned int>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::UnsignedLong::body()
    {
        return test<unsigned long>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorGreaterThan::UnsignedLongLong::body()
    {
        return test<unsigned long long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThan::UnsignedShort::body()
    {
        return test<unsigned short>({0}, {1});
    }

    //==========================================================================
    // OPERATOR LESS THAN OR EQUAL TO
    //==========================================================================

    Test::Result ListParameter_test::OperatorLessThanOrEqualTo::String::body()
    {
        return test<std::string>({"abcd"}, {"efgh"});
    }

    Test::Result ListParameter_test::OperatorLessThanOrEqualTo::Char::body()
    {
        return test<char>({'a'}, {'b'});
    }

    Test::Result ListParameter_test::OperatorLessThanOrEqualTo::Double::body()
    {
        return test<double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThanOrEqualTo::Float::body()
    {
        return test<float>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThanOrEqualTo::Int::body()
    {
        return test<int>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThanOrEqualTo::Long::body()
    {
        return test<long>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorLessThanOrEqualTo::LongDouble::body()
    {
        return test<long double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThanOrEqualTo::LongLong::body()
    {
        return test<long long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorLessThanOrEqualTo::Short::body()
    {
        return test<short>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorLessThanOrEqualTo::UnsignedChar::body()
    {
        return test<unsigned char>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorLessThanOrEqualTo::UnsignedInt::body()
    {
        return test<unsigned int>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorLessThanOrEqualTo::UnsignedLong::body()
    {
        return test<unsigned long>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorLessThanOrEqualTo::UnsignedLongLong::body()
    {
        return test<unsigned long long>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorLessThanOrEqualTo::UnsignedShort::body()
    {
        return test<unsigned short>({0}, {1});
    }

    //==========================================================================
    // OPERATOR GREATER THAN OR EQUAL TO
    //==========================================================================

    Test::Result
    ListParameter_test::OperatorGreaterThanOrEqualTo::String::body()
    {
        return test<std::string>({"abcd"}, {"efgh"});
    }

    Test::Result ListParameter_test::OperatorGreaterThanOrEqualTo::Char::body()
    {
        return test<char>({'a'}, {'b'});
    }

    Test::Result
    ListParameter_test::OperatorGreaterThanOrEqualTo::Double::body()
    {
        return test<double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThanOrEqualTo::Float::body()
    {
        return test<float>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThanOrEqualTo::Int::body()
    {
        return test<int>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThanOrEqualTo::Long::body()
    {
        return test<long>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorGreaterThanOrEqualTo::LongDouble::body()
    {
        return test<long double>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorGreaterThanOrEqualTo::LongLong::body()
    {
        return test<long long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorGreaterThanOrEqualTo::Short::body()
    {
        return test<short>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorGreaterThanOrEqualTo::UnsignedChar::body()
    {
        return test<unsigned char>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorGreaterThanOrEqualTo::UnsignedInt::body()
    {
        return test<unsigned int>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorGreaterThanOrEqualTo::UnsignedLong::body()
    {
        return test<unsigned long>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorGreaterThanOrEqualTo::UnsignedLongLong::body()
    {
        return test<unsigned long long>({0}, {1});
    }

    Test::Result
    ListParameter_test::OperatorGreaterThanOrEqualTo::UnsignedShort::body()
    {
        return test<unsigned short>({0}, {1});
    }

    //==========================================================================
    // OPERATOR EQUALITY
    //==========================================================================

    Test::Result ListParameter_test::OperatorEquality::String::body()
    {
        return test<std::string>({"abcd"}, {"efgh"});
    }

    Test::Result ListParameter_test::OperatorEquality::Char::body()
    {
        return test<char>({'a'}, {'b'});
    }

    Test::Result ListParameter_test::OperatorEquality::Double::body()
    {
        return test<double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::Float::body()
    {
        return test<float>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::Int::body()
    {
        return test<int>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::Long::body()
    {
        return test<long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::LongDouble::body()
    {
        return test<long double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::LongLong::body()
    {
        return test<long long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::Short::body()
    {
        return test<short>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::UnsignedChar::body()
    {
        return test<unsigned char>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::UnsignedInt::body()
    {
        return test<unsigned int>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::UnsignedLong::body()
    {
        return test<unsigned long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::UnsignedLongLong::body()
    {
        return test<unsigned long long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorEquality::UnsignedShort::body()
    {
        return test<unsigned short>({0}, {1});
    }

    //==========================================================================
    // OPERATOR NOT EQUAL
    //==========================================================================

    Test::Result ListParameter_test::OperatorNotEqual::String::body()
    {
        return test<std::string>({"abcd"}, {"efgh"});
    }

    Test::Result ListParameter_test::OperatorNotEqual::Char::body()
    {
        return test<char>({'a'}, {'b'});
    }

    Test::Result ListParameter_test::OperatorNotEqual::Double::body()
    {
        return test<double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::Float::body()
    {
        return test<float>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::Int::body()
    {
        return test<int>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::Long::body()
    {
        return test<long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::LongDouble::body()
    {
        return test<long double>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::LongLong::body()
    {
        return test<long long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::Short::body()
    {
        return test<short>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::UnsignedChar::body()
    {
        return test<unsigned char>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::UnsignedInt::body()
    {
        return test<unsigned int>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::UnsignedLong::body()
    {
        return test<unsigned long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::UnsignedLongLong::body()
    {
        return test<unsigned long long>({0}, {1});
    }

    Test::Result ListParameter_test::OperatorNotEqual::UnsignedShort::body()
    {
        return test<unsigned short>({0}, {1});
    }

}

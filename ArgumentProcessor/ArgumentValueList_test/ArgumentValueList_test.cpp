#include <list>
#include <string>

#include "ArgumentValueList_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ArgumentValueList.hpp"

TEST_PROGRAM_MAIN(ArgumentValueList_test);

//==============================================================================
void ArgumentValueList_test::addTestCases()
{
    ADD_TEST_CASE(Update);

    // Relational operators
    ADD_TEST_CASE(OperatorEquality);
    ADD_TEST_CASE(OperatorNotEqual);
}

//==============================================================================
void ArgumentValueList_test::Update::addTestCases()
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
template <class T> Test::Result
ArgumentValueList_test::Update::test(const std::list<T>& default_value,
                                     const std::string&  update_value,
                                     const std::list<T>& expected_value)
{
    ArgumentValueList<T> argument_value_list(default_value);

    MUST_BE_TRUE(!argument_value_list.isSet());

    argument_value_list.update(update_value);

    MUST_BE_TRUE(argument_value_list.isSet());

    std::list<T> set_value;
    argument_value_list.getValues(set_value);
    MUST_BE_TRUE(set_value == expected_value);

    return Test::PASSED;
}

//==============================================================================
// UPDATE
//==============================================================================

Test::Result ArgumentValueList_test::Update::String::body()
{
    std::list<std::string> expected_value;
    expected_value.push_back("alpha");

    return test<std::string>(std::list<std::string>(), "alpha", expected_value);
}

Test::Result ArgumentValueList_test::Update::Char::body()
{
    std::list<char> expected_value;
    expected_value.push_back('1');

    // stringstream pulls off one character at a time
    return test<char>(std::list<char>(), "111", expected_value);
}

Test::Result ArgumentValueList_test::Update::Double::body()
{
    std::list<double> expected_value;
    expected_value.push_back(111.0);

    return test<double>(std::list<double>(), "111", expected_value);
}

Test::Result ArgumentValueList_test::Update::Float::body()
{
    std::list<float> expected_value;
    expected_value.push_back(111.0f);

    return test<float>(std::list<float>(), "111", expected_value);
}

Test::Result ArgumentValueList_test::Update::Int::body()
{
    std::list<int> expected_value;
    expected_value.push_back(111);

    return test<int>(std::list<int>(), "111", expected_value);
}

Test::Result ArgumentValueList_test::Update::Long::body()
{
    std::list<long> expected_value;
    expected_value.push_back(111L);

    return test<long>(std::list<long>(), "111", expected_value);
}

Test::Result ArgumentValueList_test::Update::LongDouble::body()
{
    std::list<long double> expected_value;
    expected_value.push_back(111.0L);

    return test<long double>(std::list<long double>(), "111", expected_value);
}

Test::Result ArgumentValueList_test::Update::LongLong::body()
{
    std::list<long long> expected_value;
    expected_value.push_back(111LL);

    return test<long long>(std::list<long long>(), "111", expected_value);
}

Test::Result ArgumentValueList_test::Update::Short::body()
{
    std::list<short> expected_value;
    expected_value.push_back(static_cast<short>(111));

    return test<short>(std::list<short>(), "111", expected_value);
}

Test::Result ArgumentValueList_test::Update::UnsignedChar::body()
{
    std::list<unsigned char> expected_value;
    expected_value.push_back(static_cast<unsigned char>('1'));

    // stringstream pulls off one character at a time
    return test<unsigned char>(std::list<unsigned char>(),
                               "111",
                               expected_value);
}

Test::Result ArgumentValueList_test::Update::UnsignedInt::body()
{
    std::list<unsigned int> expected_value;
    expected_value.push_back(111U);

    return test<unsigned int>(std::list<unsigned int>(),
                              "111",
                              expected_value);
}

Test::Result ArgumentValueList_test::Update::UnsignedLong::body()
{
    std::list<unsigned long> expected_value;
    expected_value.push_back(111UL);

    return test<unsigned long>(std::list<unsigned long>(),
                               "111",
                               expected_value);
}

Test::Result ArgumentValueList_test::Update::UnsignedLongLong::body()
{
    std::list<unsigned long long> expected_value;
    expected_value.push_back(111ULL);

    return test<unsigned long long>(std::list<unsigned long long>(),
                                    "111",
                                    expected_value);
}

Test::Result ArgumentValueList_test::Update::UnsignedShort::body()
{
    std::list<unsigned short> expected_value;
    expected_value.push_back(111);

    return test<unsigned short>(std::list<unsigned short>(),
                                "111",
                                expected_value);
}

//==============================================================================
Test::Result ArgumentValueList_test::OperatorEquality::body()
{
    ArgumentValueList<int> arg0({0});
    ArgumentValueList<int> arg1({1});

    MUST_BE_TRUE(arg0 == arg0);
    MUST_BE_TRUE(!(arg0 == arg1));

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueList_test::OperatorNotEqual::body()
{
    ArgumentValueList<int> arg0({0});
    ArgumentValueList<int> arg1({1});

    MUST_BE_TRUE(arg0 != arg1);
    MUST_BE_TRUE(!(arg0 != arg0));

    return Test::PASSED;
}

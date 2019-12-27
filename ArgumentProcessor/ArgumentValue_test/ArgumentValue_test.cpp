#include <iostream>
#include <string>

#include "ArgumentValue_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(ArgumentValue_test);

//==============================================================================
void ArgumentValue_test::addTestCases()
{
    ADD_TEST_CASE(Update);
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
Test::Result ArgumentValue_test::Update::String::body()
{
    return test<std::string>("", "1234", "1234");
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Char::body()
{
    return test<char>(0, "111", 'o');
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Double::body()
{
    return test<double>(0, "111", 111.0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Float::body()
{
    return test<float>(0, "111", 111.0f);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Int::body()
{
    return test<int>(0, "111", 111);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Long::body()
{
    return test<long>(0, "111", 111L);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::LongDouble::body()
{
    return test<long double>(0, "111", 111.0L);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::LongLong::body()
{
    return test<long long>(0, "111", 111LL);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Short::body()
{
    return test<short>(0, "111", static_cast<short>(111));
}

//==============================================================================
Test::Result ArgumentValue_test::Update::UnsignedChar::body()
{
    return test<unsigned char>(0, "111", 'o');
}

//==============================================================================
Test::Result ArgumentValue_test::Update::UnsignedInt::body()
{
    return test<unsigned int>(0, "111", 111U);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::UnsignedLong::body()
{
    return test<unsigned long>(0, "111", 111);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, "111", 111ULL);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::UnsignedShort::body()
{
    return test<unsigned short>(0, "111", static_cast<unsigned short>(111));
}

//==============================================================================
template <class T>
Test::Result ArgumentValue_test::Update::test(const T&           default_value,
                                              const std::string& update_value,
                                              const T&           expected_value)
{
    ArgumentValue<T> argument_value(default_value);

    MUST_BE_TRUE(!argument_value.isSet());

    argument_value.update(update_value);

    MUST_BE_TRUE(argument_value.isSet());

    T set_value;
    argument_value.getValue(set_value);
    std::cout << set_value << "\n";
    MUST_BE_TRUE(set_value == expected_value);

    return Test::PASSED;
}

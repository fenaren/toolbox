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
    return test<std::string>("");
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Char::body()
{
    return test<char>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Double::body()
{
    return test<double>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Float::body()
{
    return test<float>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Int::body()
{
    return test<int>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Long::body()
{
    return test<long>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::LongDouble::body()
{
    return test<long double>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::LongLong::body()
{
    return test<long long>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::Short::body()
{
    return test<short>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::UnsignedChar::body()
{
    return test<unsigned char>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::UnsignedInt::body()
{
    return test<unsigned int>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::UnsignedLong::body()
{
    return test<unsigned long>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::UnsignedLongLong::body()
{
    return test<unsigned long long>(0);
}

//==============================================================================
Test::Result ArgumentValue_test::Update::UnsignedShort::body()
{
    return test<unsigned short>(0);
}

//==============================================================================
template <class T>
Test::Result ArgumentValue_test::Update::test(const T& default_value)
{
    ArgumentValue<T> argument_value(default_value);

    MUST_BE_TRUE(!argument_value.isSet());

    argument_value.update("1234");

    MUST_BE_TRUE(argument_value.isSet());

    return Test::PASSED;
}

#include <string>

#include "ConfigurationParameter_test.hpp"

#include "ConfigurationNoopParameter.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration::Parameter_test);

//=============================================================================================
void Configuration::Parameter_test::addTestCases()
{
    ADD_TEST_CASE(SetValue);
}

//=============================================================================================
void Configuration::Parameter_test::SetValue::addTestCases()
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
template <class T> Test::Result Configuration::Parameter_test::SetValue::test(
    const T& initial_value,
    const T& set_value)
{
    NoopParameter<T> configuration_value(initial_value);

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
Test::Result Configuration::Parameter_test::SetValue::Bool::body()
{
    return test<bool>(false, true);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::String::body()
{
    return test<std::string>("", "1234");
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Char::body()
{
    return test<char>(0, '1');
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Double::body()
{
    return test<double>(0, 111.0);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Float::body()
{
    return test<float>(0, 111.0f);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Int::body()
{
    return test<int>(0, 111);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Long::body()
{
    return test<long>(0, 111L);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::LongDouble::body()
{
    return test<long double>(0, 111.0L);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::LongLong::body()
{
    return test<long long>(0, 111LL);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Short::body()
{
    return test<short>(0, static_cast<short>(111));
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::UnsignedChar::body()
{
    return test<unsigned char>(0, static_cast<unsigned char>('1'));
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::UnsignedInt::body()
{
    return test<unsigned int>(0, 111U);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::UnsignedLong::body()
{
    return test<unsigned long>(0, 111);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 111ULL);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::UnsignedShort::body()
{
    return test<unsigned short>(0, static_cast<unsigned short>(111));
}

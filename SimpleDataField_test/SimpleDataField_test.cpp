#include <cstdint>
#include <iostream>
#include <list>

#include "SimpleDataField_test.hpp"

#include "SimpleDataField.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(SimpleDataField_test);

//==============================================================================
void SimpleDataField_test::addTestCases()
{
    ADD_TEST_CASE(GetLengthBytes);
    ADD_TEST_CASE(GetValue);
    ADD_TEST_CASE(ReadRaw);
    ADD_TEST_CASE(SimpleAssignment);
    ADD_TEST_CASE(WriteRaw);
}

//==============================================================================
void SimpleDataField_test::GetLengthBytes::addTestCases()
{
    ADD_TEST_CASE(Char);
/*    ADD_TEST_CASE(Double);
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
    ADD_TEST_CASE(UnsignedShort);*/
}

//==============================================================================
void SimpleDataField_test::GetValue::addTestCases()
{
    ADD_TEST_CASE(Char);
/*    ADD_TEST_CASE(Double);
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
    ADD_TEST_CASE(UnsignedShort);j*/
}

//==============================================================================
void SimpleDataField_test::ReadRaw::addTestCases()
{
    ADD_TEST_CASE(Char);
/*    ADD_TEST_CASE(Double);
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
    ADD_TEST_CASE(UnsignedShort);*/
}

//==============================================================================
void SimpleDataField_test::SimpleAssignment::addTestCases()
{
    ADD_TEST_CASE(Char);
/*    ADD_TEST_CASE(Double);
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
    ADD_TEST_CASE(UnsignedShort);*/
}

//==============================================================================
void SimpleDataField_test::WriteRaw::addTestCases()
{
    ADD_TEST_CASE(Char);
/*    ADD_TEST_CASE(Double);
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
    ADD_TEST_CASE(UnsignedShort);*/
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::Char::body()
{
    return test<char>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::Char::body()
{
    return test<char>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::Char::body()
{
    return test<char>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::Char::body()
{
    return test<char>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::Char::body()
{
    return test<char>();
}

//==============================================================================
template <class T> Test::Result SimpleDataField_test::GetLengthBytes::test()
{
    SimpleDataField<T> test_sdf;
    MUST_BE_TRUE(test_sdf.getLengthBytes() == sizeof(T));
    return Test::PASSED;
}

//==============================================================================
template <class T> Test::Result SimpleDataField_test::GetValue::test()
{
    SimpleDataField<T> test_sdf(0);
    test_sdf.simple_data_field = 1;
    MUST_BE_TRUE(test_sdf.getValue() == 1);
    return Test::PASSED;
}

//==============================================================================
template <class T> Test::Result SimpleDataField_test::ReadRaw::test()
{
    SimpleDataField<T> test_sdf(0);
    T intrinsic_type = 1;
    test_sdf.DataField::readRaw(
        reinterpret_cast<std::uint8_t*>(&intrinsic_type));
    MUST_BE_TRUE(test_sdf.getValue() == 1);
    return Test::PASSED;
}

//==============================================================================
template <class T> Test::Result SimpleDataField_test::SimpleAssignment::test()
{
    SimpleDataField<T> test_sdf;
    test_sdf = 1;
    MUST_BE_TRUE(test_sdf.simple_data_field == 1);
    return Test::SKIPPED;
}

//==============================================================================
template <class T> Test::Result SimpleDataField_test::WriteRaw::test()
{
    SimpleDataField<T> test_sdf(1);
    T intrinsic_type = 0;
    test_sdf.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&intrinsic_type));
    MUST_BE_TRUE(intrinsic_type == 1);
    return Test::PASSED;
}

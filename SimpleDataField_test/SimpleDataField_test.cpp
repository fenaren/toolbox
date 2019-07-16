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
void SimpleDataField_test::GetValue::addTestCases()
{
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
void SimpleDataField_test::ReadRaw::addTestCases()
{
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
void SimpleDataField_test::SimpleAssignment::addTestCases()
{
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
void SimpleDataField_test::WriteRaw::addTestCases()
{
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
Test::Result SimpleDataField_test::GetLengthBytes::Char::body()
{
    return test<char>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::Double::body()
{
    return test<double>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::Float::body()
{
    return test<float>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::Int::body()
{
    return test<int>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::Long::body()
{
    return test<long>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::LongDouble::body()
{
    return test<long double>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::LongLong::body()
{
    return test<long long>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::Short::body()
{
    return test<short>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::UnsignedChar::body()
{
    return test<unsigned char>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::UnsignedInt::body()
{
    return test<unsigned int>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::UnsignedLong::body()
{
    return test<unsigned long>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::UnsignedLongLong::body()
{
    return test<unsigned long long>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetLengthBytes::UnsignedShort::body()
{
    return test<unsigned short>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::Char::body()
{
    return test<char>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::Double::body()
{
    return test<double>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::Float::body()
{
    return test<float>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::Int::body()
{
    return test<int>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::Long::body()
{
    return test<long>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::LongDouble::body()
{
    return test<long double>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::LongLong::body()
{
    return test<long long>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::Short::body()
{
    return test<short>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::UnsignedChar::body()
{
    return test<unsigned char>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::UnsignedInt::body()
{
    return test<unsigned int>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::UnsignedLong::body()
{
    return test<unsigned long>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::UnsignedLongLong::body()
{
    return test<unsigned long long>();
}

//==============================================================================
Test::Result SimpleDataField_test::GetValue::UnsignedShort::body()
{
    return test<unsigned short>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::Char::body()
{
    return test<char>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::Double::body()
{
    return test<double>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::Float::body()
{
    return test<float>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::Int::body()
{
    return test<int>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::Long::body()
{
    return test<long>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::LongDouble::body()
{
    return test<long double>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::LongLong::body()
{
    return test<long long>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::Short::body()
{
    return test<short>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::UnsignedChar::body()
{
    return test<unsigned char>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::UnsignedInt::body()
{
    return test<unsigned int>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::UnsignedLong::body()
{
    return test<unsigned long>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::UnsignedLongLong::body()
{
    return test<unsigned long long>();
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::UnsignedShort::body()
{
    return test<unsigned short>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::Char::body()
{
    return test<char>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::Double::body()
{
    return test<double>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::Float::body()
{
    return test<float>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::Int::body()
{
    return test<int>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::Long::body()
{
    return test<long>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::LongDouble::body()
{
    return test<long double>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::LongLong::body()
{
    return test<long long>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::Short::body()
{
    return test<short>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::UnsignedChar::body()
{
    return test<unsigned char>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::UnsignedInt::body()
{
    return test<unsigned int>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::UnsignedLong::body()
{
    return test<unsigned long>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::UnsignedLongLong::body()
{
    return test<unsigned long long>();
}

//==============================================================================
Test::Result SimpleDataField_test::SimpleAssignment::UnsignedShort::body()
{
    return test<unsigned short>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::Char::body()
{
    return test<char>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::Double::body()
{
    return test<double>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::Float::body()
{
    return test<float>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::Int::body()
{
    return test<int>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::Long::body()
{
    return test<long>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::LongDouble::body()
{
    return test<long double>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::LongLong::body()
{
    return test<long long>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::Short::body()
{
    return test<short>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::UnsignedChar::body()
{
    return test<unsigned char>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::UnsignedInt::body()
{
    return test<unsigned int>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::UnsignedLong::body()
{
    return test<unsigned long>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::UnsignedLongLong::body()
{
    return test<unsigned long long>();
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::UnsignedShort::body()
{
    return test<unsigned short>();
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

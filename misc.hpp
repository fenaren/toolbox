#if !defined MISC_HPP
#define MISC_HPP

// For functionality that has no obvious home elsewhere

#include <cstdint>

#define BITS_PER_BYTE 8

namespace misc
{
    // This would be BIG_ENDIAN and LITTLE_ENDIAN but those names collide with
    // existing symbols on MacOS.
    enum ByteOrder
    {
        ENDIAN_BIG,
        ENDIAN_LITTLE
    };

    // As of this writing, this is used by BitField and ByteField to determine
    // how their data is indexed.  "MS_ZERO" stands for "Most Significant Zero"
    // and means the most significant unit of data, when data is interpreted as
    // a number, is assigned index 0.  "LS_ZERO" stands for "Least Significant
    // Zero" and means the least significant unit of data, when data is
    // interpreted as a number, is assigned index 0.  The rest of the indices
    // are assigned in order of increasing or decreasing significance as
    // appropriate and expected.
    enum DataIndexingMode
    {
        MS_ZERO,
        LS_ZERO
    };

    // Determines byte ordering (endianness) of the host
    ByteOrder getByteOrder();

    // Does an in-place byteswap of the data at "buffer" of length "len".  For
    // example a "len" value of 4 would be used for swapping a single 32-bit
    // integer.
    void byteswap(std::uint8_t* buffer, unsigned int len);

    // Does an out-of-place byteswap.  The data at "source" is copied into
    // "destination" byteswapped.  The data at "source" is not modified.  This
    // is logically equivalent to a memcpy followed by a call to the
    // two-argument byteswap function defined above but should be faster.
    void byteswap(std::uint8_t*       destination,
                  const std::uint8_t* source,
                  unsigned int        len);

    // Convenience wrapper meant for swapping fundamental data types.  Removes
    // the need for the user to deal with casting and sizing.
    template <class T> void byteswap(T& swapme);

    // Returns true if a and b are within epsilon of each other, false otherwise
    bool withinEpsilonOf(double a, double b, double epsilon);

    // Does what it says on the tin; returns the smallest multiple of x that is
    // greater than or equal to y.
    long smallestMultipleOfXGreaterOrEqualToY(long x, long y);
};

// Overloads operator! to take a misc::ByteOrder and return the "other" value.
// If given misc::BIG_ENDIAN, return misc::LITTLE_ENDIAN.  If given
// misc::LITTLE_ENDIAN, return misc::BIG_ENDIAN.  There are only two possible
// endianness settings, and being able to invert one into the other is handy and
// seemingly appropriate for operator!.
misc::ByteOrder operator!(const misc::ByteOrder& byte_order);

#endif

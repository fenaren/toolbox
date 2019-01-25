#if !defined MISC_HPP
#define MISC_HPP

// For functionality that has no obvious home elsewhere

#define BITS_PER_BYTE 8

namespace misc
{
    enum ByteOrder
    {
        ENDIAN_BIG,
        ENDIAN_LITTLE
    };

    // Determines byte ordering (endianness) of the host
    ByteOrder getByteOrder();

    // Does an in-place byteswap of the data at "buffer" of length "len".  For
    // example a "len" value of 4 would be used for swapping a single 32-bit
    // integer.
    void byteswap(unsigned char* buffer, unsigned int len);

    // Does an out-of-place byteswap.  The data at "source" is copied into
    // "destination" byteswapped.  The data at "source" is not modified.  This
    // is logically equivalent to a memcpy followed by a call to the
    // two-argument byteswap function defined above but should be faster.
    void byteswap(unsigned char*       destination,
                  const unsigned char* source,
                  unsigned int         len);

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

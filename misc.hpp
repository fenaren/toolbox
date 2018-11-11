#if !defined MISC_HPP
#define MISC_HPP

// For functionality that has no obvious home elsewhere

// BIG_ENDIAN and LITTLE_ENDIAN are defined on macOS for some reason or other.
// Replace those definitions with the ones defined in here.

#if defined BIG_ENDIAN
#undef BIG_ENDIAN
#endif

#if defined LITTLE_ENDIAN
#undef LITTLE_ENDIAN
#endif

namespace misc
{
    enum ByteOrder
    {
        BIG_ENDIAN,
        LITTLE_ENDIAN
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
};

// Overloads operator! to take a misc::ByteOrder and return the "other" value.
// If given misc::BIG_ENDIAN, return misc::LITTLE_ENDIAN.  If given
// misc::LITTLE_ENDIAN, return misc::BIG_ENDIAN.  There are only two possible
// endianness settings, and being able to invert one into the other is handy and
// seemingly appropriate for operator!.
misc::ByteOrder operator!(const misc::ByteOrder& byte_order);

#endif

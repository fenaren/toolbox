// For functionality that has no obvious home elsewhere

#if !defined MISC_HPP
#define MISC_HPP

// BIG_ENDIAN and LITTLE_ENDIAN are defined on macOS for some reason or other.
// Get rid of that definition and replace with this one.

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
};

#endif

#include "misc.hpp"

// Determines byte ordering (endianness) of the host
misc::ByteOrder misc::getByteOrder()
{
    unsigned short test_var = 0xff00;
    if (*(unsigned char*)&test_var > 0)
    {
        return BIG_ENDIAN;
    }
    else
    {
        return LITTLE_ENDIAN;
    }
}

//==============================================================================
// Byteswaps the buffer of memory at "buffer" of length "len".  For example a
// "len" value of 4 would be used for swapping a single 32-bit integer
//==============================================================================
void misc::byteswap(unsigned char* buffer, unsigned int len)
{
    // Work from both sides of "buffer" simultaneously
    for (unsigned int i = 0; i < len / 2; i++)
    {
        // A standard 3-step swap
        unsigned char temp = buffer[i];
        buffer[i] = buffer[(len - i) - 1];
        buffer[(len - i) - 1] = temp;
    }
}

//==============================================================================
// Does an out-of-place byteswap.  The data at "source" is copied into
// "destination" byteswapped.  The data at "source" is not modified.  This is
// logically equivalent to a memcpy followed by a call to the two-argument
// byteswap function defined above but should be faster.
//==============================================================================
void misc::byteswap(unsigned char*       destination,
                    const unsigned char* source,
                    unsigned int         len)
{
    // Work from opposite sides of "destination" and "source" simultaneously
    for (unsigned int i = 0; i < len; i++)
    {
        destination[i] = source[(len - i) - 1];
    }
}

//==============================================================================
// Convenience wrapper meant for swapping fundamental data types.  Removes the
// need for the user to deal with casting and sizing.  Explicit instantiations
// of this function for all the fundamental types is below.
//==============================================================================
template <class T> void misc::byteswap(T& swapme)
{
    misc::byteswap(reinterpret_cast<unsigned char*>(&swapme), sizeof(T));
}

template void misc::byteswap(char&);
template void misc::byteswap(double&);
template void misc::byteswap(float&);
template void misc::byteswap(int&);
template void misc::byteswap(long&);
template void misc::byteswap(long double&);
template void misc::byteswap(long long&);
template void misc::byteswap(short&);
template void misc::byteswap(unsigned char&);
template void misc::byteswap(unsigned int&);
template void misc::byteswap(unsigned long&);
template void misc::byteswap(unsigned long long&);
template void misc::byteswap(unsigned short&);

//==============================================================================
// Overloads operator! to take a misc::ByteOrder and return the "other" value.
// If given misc::BIG_ENDIAN, return misc::LITTLE_ENDIAN.  If given
// misc::LITTLE_ENDIAN, return misc::BIG_ENDIAN.  There are only two possible
// endianness settings, and being able to invert one into the other is handy and
// seemingly appropriate for operator!.
//==============================================================================
misc::ByteOrder operator!(const misc::ByteOrder& byte_order)
{
    if (byte_order == misc::BIG_ENDIAN)
    {
        return misc::LITTLE_ENDIAN;
    }

    return misc::BIG_ENDIAN;
}

#include <cmath>
#include <cstdlib>

#include "misc.hpp"

//==============================================================================
misc::ByteOrder misc::getByteOrder()
{
    int something[4];
    unsigned short test_var = 0xff00;
    if (*(unsigned char*)&test_var > 0)
    {
        return ENDIAN_BIG;
    }
    else
    {
        return ENDIAN_LITTLE;
    }
}

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
template <class T> void misc::byteswap(T& swapme)
{
    misc::byteswap(reinterpret_cast<unsigned char*>(&swapme), sizeof(T));
}

// Explicit instantiations of templatized byteswap for all the fundamental types
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
bool misc::withinEpsilonOf(double a, double b, double epsilon)
{
    return a <= (b + epsilon) && a >= (b - epsilon);
}

//==============================================================================
long misc::smallestMultipleOfXGreaterOrEqualToY(long x, long y)
{
    std::ldiv_t div_result = std::ldiv(y, x);

    if (div_result.rem != 0)
    {
        div_result.quot += 1;
    }

    return div_result.quot * x;
}

//==============================================================================
misc::ByteOrder operator!(const misc::ByteOrder& byte_order)
{
    if (byte_order == misc::ENDIAN_BIG)
    {
        return misc::ENDIAN_LITTLE;
    }

    return misc::ENDIAN_BIG;
}

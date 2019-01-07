#include <cstring>

#include "misc.hpp"
#include "pullUpdatePush.hpp"

//==============================================================================
// Does a couple things for hard-to-understand reasons.
//
// First we pull what we pull a T out of the memory starting at raw_dptest +
// offset (this function is used multiple times in succession and, as can be
// seen on the last line, offset is bumped each time, meaning a new section of
// memory is read each time).  Because we should have written this memory in the
// byte ordering that is opposite of this host system, this T has to be
// byteswapped again to be sensical.  This value is then left alone to be
// returned in the "dptest_var" argument.
//
// Second, we save a copy of an incremented "dptest_var" into
// "dptest_var_updated".  This value is then written byteswapped into the same
// memory location we read as described in the paragraph above, meaning the
// memory location is now incremented but otherwise unchanged.  Later, readRaw()
// will read this, and we can test for presence of the incremented value.
//
// Lastly, offset is bumped past the memory location we read with it to prepare
// for its next usage.
//==============================================================================
template <class T>
void pullUpdatePush(unsigned char* raw_dptest,
                    T&             dptest_var,
                    T&             dptest_var_updated,
                    unsigned int&  offset,
                    bool           swap)
{
    // Pull a field from the raw packet and swap to make it legible
    memcpy(&dptest_var, raw_dptest + offset, sizeof(T));

    if (swap)
    {
        misc::byteswap(
            reinterpret_cast<unsigned char*>(&dptest_var), sizeof(T));
    }

    // Increment the retrieved field but store it in a different place
    dptest_var_updated = dptest_var + 1;

    if (swap)
    {
        // Have to swap to the wrong byte order to the readRaw later in the test
        // will hopefully correct the swap
        misc::byteswap(raw_dptest + offset,
                       reinterpret_cast<unsigned char*>(&dptest_var_updated),
                       sizeof(T));
    }
    else
    {
        // Pull a field from the raw packet and swap to make it legible
        memcpy(raw_dptest + offset,
               reinterpret_cast<unsigned char*>(&dptest_var_updated),
               sizeof(T));
    }

    // Bump this for successive calls
    offset += sizeof(T);
}

#define PUP_INSTANTIATE(T)                                          \
    template void pullUpdatePush(unsigned char* raw_dptest,         \
                                 T&             dptest_var,         \
                                 T&             dptest_var_updated, \
                                 unsigned int&  offset,             \
                                 bool           swap);

PUP_INSTANTIATE(char);
PUP_INSTANTIATE(double);
PUP_INSTANTIATE(float);
PUP_INSTANTIATE(int);

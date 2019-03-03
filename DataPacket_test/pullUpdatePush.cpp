#include <cstdint>
#include <cstring>

#include "misc.hpp"
#include "pullUpdatePush.hpp"

//==============================================================================
template <class T>
void pullUpdatePush(std::uint8_t* raw_dptest,
                    T&            dptest_var,
                    T&            dptest_var_updated,
                    unsigned int& offset,
                    bool          swap)
{
    // Pull a field from the raw packet and swap to make it legible
    memcpy(&dptest_var, raw_dptest + offset, sizeof(T));

    if (swap)
    {
        misc::byteswap(
            reinterpret_cast<std::uint8_t*>(&dptest_var), sizeof(T));
    }

    // Increment the retrieved field but store it in a different place
    dptest_var_updated = dptest_var + 1;

    if (swap)
    {
        // Have to swap to the wrong byte order to the readRaw later in the test
        // will hopefully correct the swap
        misc::byteswap(raw_dptest + offset,
                       reinterpret_cast<std::uint8_t*>(&dptest_var_updated),
                       sizeof(T));
    }
    else
    {
        // Pull a field from the raw packet and swap to make it legible
        memcpy(raw_dptest + offset,
               reinterpret_cast<std::uint8_t*>(&dptest_var_updated),
               sizeof(T));
    }

    // Bump this for successive calls
    offset += sizeof(T);
}

#define PUP_INSTANTIATE(T)                                          \
    template void pullUpdatePush(std::uint8_t* raw_dptest,         \
                                 T&            dptest_var,         \
                                 T&            dptest_var_updated, \
                                 unsigned int& offset,             \
                                 bool          swap);

PUP_INSTANTIATE(char);
PUP_INSTANTIATE(double);
PUP_INSTANTIATE(float);
PUP_INSTANTIATE(int);

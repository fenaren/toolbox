#if !defined NETWORK_ADDRESS_HPP
#define NETWORK_ADDRESS_HPP

#include <vector>

class NetworkAddress : public std::vector<char>
{
public:

    // Constructs a new NetworkAddress.
    // cppcheck-suppress noExplicitConstructor
    NetworkAddress(unsigned short length_bytes);

    // Destroys a NetworkAddress; does nothing, since this class doesn't
    // dynamically allocate memory.
    virtual ~NetworkAddress();

    // Reads a raw 4-byte IPv4 address from memory, "buf" is assumed to point to
    // a valid IPv4 address
    void readRaw(const char* buf);

    // Writes a raw 4-byte IPv4 address to memory, "buf" is assumed to point to
    // 4 bytes of properly allocated and available memory
    void writeRaw(char* buf) const;
};

#endif

#if !defined NETWORK_ADDRESS_HPP
#define NETWORK_ADDRESS_HPP

#include <vector>

class NetworkAddress : public std::vector<char>
{
public:

    // Constructs a new NetworkAddress.
    NetworkAddress(unsigned short length_bytes);

    // Destroys a NetworkAddress; does nothing, since this class doesn't
    // dynamically allocate memory.
    virtual ~NetworkAddress();

    // Reads a raw network address from memory, "buf" is assumed to point to a
    // valid network address of length this->size()
    void readRaw(const char* buf);

    // Writes a raw network address to memory, "buf" is assumed to point to
    // this->size() bytes of properly allocated and available memory
    void writeRaw(char* buf) const;
};

#endif

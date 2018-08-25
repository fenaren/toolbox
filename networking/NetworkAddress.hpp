#if !defined NETWORK_ADDRESS_HPP
#define NETWORK_ADDRESS_HPP

#include <vector>

class NetworkAddress : public std::vector<unsigned char>
{
public:

    // Constructs a new NetworkAddress of the specified length; data is
    // initialized to all 0s
    NetworkAddress(unsigned short length_bytes);

    // Constructs a new NetworkAddress of the specified length containing a copy
    // of the data at the specified location; only "length_bytes" amount of data
    // is internalized
    NetworkAddress(const unsigned char* raw_address,
                   unsigned short       length_bytes);

    // Destroys a NetworkAddress; does nothing, since this class doesn't
    // dynamically allocate memory.
    virtual ~NetworkAddress();

    // Reads a raw network address from memory, "buf" is assumed to point to a
    // valid network address of length this->size()
    void readRaw(const unsigned char* buf);

    // Writes a raw network address to memory, "buf" is assumed to point to
    // this->size() bytes of properly allocated and available memory
    void writeRaw(unsigned char* buf) const;
};

#endif

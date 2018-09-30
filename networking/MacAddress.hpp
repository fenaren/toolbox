#if !defined MAC_ADDRESS_HPP
#define MAC_ADDRESS_HPP

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "NetworkAddress.hpp"

class MacAddress : public NetworkAddress
{
  public:

    // Constructs a new MacAddress, initialized to 00:00:00:00:00:00
    MacAddress();

    // Constructs a new MacAddress, initialzed to a copy of the data at the
    // indicated location
    explicit MacAddress(const unsigned char* buffer);

    // Constructs a new MacAddress matching the given string representation.
    explicit MacAddress(const std::string& mac_address_str);

    // Copy constructor
    //explicit MacAddress(const MacAddress& mac_address);

    // Defines how to convert a MacAddress to a std::string
    operator std::string() const;

    // Destroys a MacAddress; does nothing, since this class doesn't dynamically
    // allocate memory.
    virtual ~MacAddress();

    MacAddress& operator=(const std::string& mac_address_str);

    // MAC addresses are this many bytes long
    static const unsigned short LENGTH_BYTES = 6;

    // MAC address strings are this many characters long
    static const unsigned short MAX_STR_LENGTH_CHARS = 18;

private:

    unsigned char mac_address_raw[LENGTH_BYTES];
};

std::ostream& operator<<(std::ostream& os, const MacAddress& mac_address);

std::istream& operator>>(std::istream& is, MacAddress& mac_address);

bool operator==(const MacAddress&  mac_address1,
                const MacAddress&  mac_address2);
bool operator==(const MacAddress&  mac_address1,
                const std::string& mac_address2);
bool operator==(const std::string& mac_address1,
                const MacAddress&  mac_address2);

bool operator!=(const MacAddress&  mac_address1,
                const MacAddress&  mac_address2);
bool operator!=(const MacAddress&  mac_address1,
                const std::string& mac_address2);
bool operator!=(const std::string& mac_address1,
                const MacAddress&  mac_address2);

#endif

#if !defined MAC_ADDRESS_HPP
#define MAC_ADDRESS_HPP

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "Data.hpp"

class MacAddress : public std::vector<char>
{
  public:

    // Constructs a new MacAddress.
    MacAddress();

    // Constructs a new MacAddress matching the given string representation.
    MacAddress(const std::string& mac_address_str);

    // Copy constructor
    MacAddress(const MacAddress& mac_address);

    // Destroys a MacAddress; does nothing, since this class doesn't dynamically
    // allocate memory.
    ~MacAddress();

    // Writes string representation of self to the given string
    bool toString(std::string& mac_address_str) const;

    // MAC addresses are this long
    static const unsigned int length = 6;
};

// Writes a string representation of this MAC address
std::ostream& operator<<(std::ostream& os, MacAddress& mac_address);

// Reads a string representation of this MAC address
std::istream& operator>>(std::istream& is, MacAddress& mac_address);

#endif

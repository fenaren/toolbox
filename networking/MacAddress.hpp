#if !defined MAC_ADDRESS_HPP
#define MAC_ADDRESS_HPP

#include <istream>
#include <ostream>
#include <string>

#include "Data.hpp"

class MacAddress : public Data
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

    // Assigns one MAC address to another
    MacAddress& operator=(const MacAddress& mac_address);

    // Assigns a string to a MAC address
    MacAddress& operator=(const std::string& mac_address_str);

    // Allows the use of brackets to index into the MAC address
    char& operator[](const unsigned int byteNum);

    // Compares for equality with the given MacAddress
    bool operator==(const MacAddress& mac_address) const;

    // Compares for equality with the given MAC address string
    bool operator==(const std::string& mac_address_str) const;

    // Compares for inequality with the given MacAddress
    bool operator!=(const MacAddress& mac_address) const;

    // Compares for inequality with the given MAC address string
    bool operator!=(const std::string& mac_address_str) const;

    // MAC addresses are this long
    static const unsigned int length = 6;

  private:

    // The six bytes of the MAC address
    char mac_address[length];
};

// Writes a string representation of this MAC address
std::ostream& operator<<(std::ostream& os, MacAddress& mac_address);

// Reads a string representation of this MAC address
std::istream& operator>>(std::istream& is, MacAddress& mac_address);

#endif

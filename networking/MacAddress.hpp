#if !defined MAC_ADDRESS_HPP
#define MAC_ADDRESS_HPP

#include <istream>
#include <ostream>

class MacAddress
{
  public:

    // Constructs a new MacAddress.
    MacAddress();

    // Destroys a MacAddress; does nothing, since this class doesn't dynamically
    // allocate memory.
    ~MacAddress();

    // Copy constructor
    MacAddress(const MacAddress& mac_address);

    // Assigns one MAC address to another
    MacAddress& operator=(const MacAddress& mac_address);

    // Compares two MAC addresses for equality
    bool operator==(const MacAddress& mac_address);

    // Allows the use of brackets to index into the MAC address
    unsigned char& operator[](const unsigned int byteNum);

  private:

    // The six bytes of the MAC address
    unsigned char mac_address[6];
};

// Writes a string representation of this MAC address
std::ostream& operator<<(std::ostream& os, MacAddress& mac_address);

// Reads a string representation of this MAC address
std::istream& operator>>(std::istream& is, MacAddress& mac_address);

#endif

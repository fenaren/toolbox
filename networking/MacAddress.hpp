#if !defined MAC_ADDRESS_HPP
#define MAC_ADDRESS_HPP

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

    // MacAddress assignment
    MacAddress operator=(const MacAddress& mac_address);

    // MacAddress equality
    bool operator==(const MacAddress& mac_address);

    unsigned char& operator[](const unsigned int byteNum);

  private:

    // The six bytes of the MAC address
    unsigned char mac_address[6];
};

// Writes a string representation of this MAC address
std::ostream& operator<<(std::ostream& os, MacAddress& mac_address);

#endif

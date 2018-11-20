#if !defined IPV4_HEADER_HPP
#define IPV4_HEADER_HPP

#include "DataPacket.hpp"

class Ipv4Header : public DataPacket
{
public:

    // Frobnicates the widget
    Ipv4Header();

    // Defrobnicates the widget
    virtual ~Ipv4Header();

private:

    // Copy construction and assignment not allowed
    Ipv4Header(const Ipv4Header&);
    Ipv4Header& operator=(const Ipv4Header&);
};

#endif

#if !defined ETHERTYPE_HPP
#define ETHERTYPE_HPP

namespace Ethertype
{
    // Shorthand textual ways of referencing some Ethertypes
    enum Ethertype
    {
        IPV4 = 0x0800,
        ARP  = 0x0806
    };
}

#endif

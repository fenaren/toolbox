// Ethernet II frame header

#if !defined(ETHERNET_II_HEADER_H)
#define ETHERNET_II_HEADER_H

struct ethernet_ii_header
{
    // MAC of destination device
    char mac_destination[6];

    // MAC of source device
    char mac_source[6];

    // Ethertype
    char ethertype[2];
};

#endif

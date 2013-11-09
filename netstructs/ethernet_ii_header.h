// Ethernet II frame header
// Leigh Garbs

#if !defined(ETHERNET_II_HEADER_H)
#define ETHERNET_II_HEADER_H

struct ethernet_ii_header
{
  // MAC of destination device
  unsigned char mac_destination[6];

  // MAC of source device
  unsigned char mac_source[6];

  // Ethertype
  unsigned char ethertype[2];
};

#endif

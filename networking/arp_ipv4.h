// ARP packet for IPv4
// Leigh Garbs

#if !defined(ARP_IPV4_H)
#define ARP_IPV4_H

struct arp_ipv4
{
  // Link layer protocol type
  char htype[2];

  // Network layer protocol type
  char ptype[2];

  // Length of hardware addresses in bytes
  char hlen[1];

  // Length of protocol addresses in bytes
  char plen[1];

  // ARP operation; 1 for request, 2 for reply
  char oper[2];

  // Sender hardware address
  char sha[6];

  // Sender protocol address
  char spa[4];

  // Target hardware address
  char tha[6];

  // Target protocol address
  char tpa[4];
};

#endif

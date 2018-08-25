// ARP packet for IPv4

#if !defined(ARP_IPV4_H)
#define ARP_IPV4_H

struct arp_ipv4
{
    // Link layer protocol type
    unsigned char htype[2];

    // Network layer protocol type
    unsigned char ptype[2];

    // Length of hardware addresses in bytes
    unsigned char hlen[1];

    // Length of protocol addresses in bytes
    unsigned char plen[1];

    // ARP operation; 1 for request, 2 for reply
    unsigned char oper[2];

    // Sender hardware address
    unsigned char sha[6];

    // Sender protocol address
    unsigned char spa[4];

    // Target hardware address
    unsigned char tha[6];

    // Target protocol address
    unsigned char tpa[4];
};

#endif

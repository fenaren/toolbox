// UDP packet header

#if !defined(UDP_HEADER_H)
#define UDP_HEADER_H

struct udp_header
{
    // Source port
    unsigned char source_port[2];

    // Destination port
    unsigned char destination_port[2];

    // How many bytes are in the payload
    unsigned char length[2];

    // Checksum over pseudo-header, header, and data
    unsigned char checksum[2];
}

#endif

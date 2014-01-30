// IPv4 packet header
// Leigh Garbs

#if !defined(IPV4_HEADER_H)
#define IPV4_HEADER_H

struct ipv4_header
{
  // Bits 0-3: IP version # (4 for IPv4); bits 4-7: header length in 32-bit
  // words
  char version_headerlen[1];

  // Bits 8-13: Differentiated Services Code Point; bits 14-15: Explicit
  // Congestion Notification
  char dscp_ecn[1];

  // Total packet length (header + data) in bytes
  char total_length[2];

  // Identification
  char id[2];

  // Bits 0-2: flags (bit 0 reserved, bit 1 don't fragment, bit 2 more
  // fragments); bits 3-15: fragment offset
  char flags_fragoffset[2];

  // Packet time-to-live
  char ttl[1];

  // Protocol contained in payload
  char protocol[1];

  // Header checksum
  char header_cksum[2];

  // Source IP address
  char source_ip[4];

  // Destination IP address
  char destination_ip[4];
};

#endif

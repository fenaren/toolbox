#include <cstdio>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netdb.h>
#include <netpacket/packet.h>
#include <poll.h>
#include <sstream>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "LinuxRawSocket.hpp"

#include "LinuxSocketCommon.hpp"

//====================================================================
// Creates a Linux raw socket
//====================================================================
LinuxRawSocket::LinuxRawSocket()
{
    // Zero out input and output interface structures
    memset(&input_interface,  0, sizeof(sockaddr_ll));
    memset(&output_interface, 0, sizeof(sockaddr_ll));

    // Fill in common interface information
    input_interface.sll_family   = AF_PACKET;
    input_interface.sll_protocol = htons(ETH_P_ALL);
    input_interface.sll_ifindex  = 0;

    output_interface.sll_family   = AF_PACKET;
    output_interface.sll_protocol = htons(ETH_P_ALL);
    output_interface.sll_ifindex  = 1;
    output_interface.sll_halen    = 6;

    blocking_timeout = -1.0;

    ts_blocking_timeout.tv_sec  = 0;
    ts_blocking_timeout.tv_nsec = 0;

    // Create the socket; third argument specifies which Ethernet protocols are
    // received, current setting is all
    socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    // Check for errors
    if (socket_fd == -1)
    {
        perror("LinuxRawSocket::LinuxRawSocket");
    }
}

//====================================================================
// Shuts this socket down
//====================================================================
LinuxRawSocket::~LinuxRawSocket()
{
    LinuxSocketCommon::shutdown(socket_fd);
}

//====================================================================
// Enables blocking
//====================================================================
bool LinuxRawSocket::enableBlocking()
{
    return LinuxSocketCommon::enableBlocking(socket_fd);
}

//====================================================================
// Disables blocking
//====================================================================
bool LinuxRawSocket::disableBlocking()
{
    return LinuxSocketCommon::disableBlocking(socket_fd);
}

//====================================================================
// Returns blocking status
//====================================================================
bool LinuxRawSocket::isBlockingEnabled()
{
    return LinuxSocketCommon::isBlockingEnabled(socket_fd);
}

//====================================================================
// Sets the current blocking timeout
//====================================================================
void LinuxRawSocket::setBlockingTimeout(double blocking_timeout)
{
    LinuxSocketCommon::setBlockingTimeout(blocking_timeout,
                                          this->blocking_timeout,
                                          ts_blocking_timeout);
}

//====================================================================
// Gets the current blocking timeout
//====================================================================
double LinuxRawSocket::getBlockingTimeout() const
{
    return blocking_timeout;
}

//====================================================================
// Sets the interface this socket will get data from
//====================================================================
bool LinuxRawSocket::setInputInterface(const std::string& interface_name)
{
    // Operation cannot complete successfully without an open socket
    if (socket_fd == -1)
    {
        return false;
    }

    // Determine appropriate interface number, or 0 for all interfaces
    if (interface_name == "")
    {
        input_interface.sll_ifindex = 0;
    }
    else
    {
        input_interface.sll_ifindex = getInterfaceIndex(interface_name);
    }

    // Now attempt to bind this socket to the desired interface
    if (bind(socket_fd,
             (const sockaddr*)&input_interface,
             sizeof(sockaddr_ll)) == -1)
    {
        perror("LinuxRawSocket::setInputInterface");
        return false;
    }

    return true;
}

//====================================================================
// Set the interface this socket will send data to
//====================================================================
bool LinuxRawSocket::setOutputInterface(const std::string& interface_name)
{
    // Operation cannot complete successfully without an open socket
    if (socket_fd == -1)
    {
        return false;
    }

    // Retrieve the index of the desired interface
    output_interface.sll_ifindex = getInterfaceIndex(interface_name);

    return true;
}

//====================================================================
// Reads data from socket into buffer
//====================================================================
int LinuxRawSocket::read(char* buffer, unsigned int size)
{
    return LinuxSocketCommon::read(
        socket_fd,
        buffer,
        size,
        blocking_timeout,
        ts_blocking_timeout,
        reinterpret_cast<sockaddr*>(&input_interface),
        sizeof(sockaddr_ll));
}

//====================================================================
// Writes data to socket
//====================================================================
int LinuxRawSocket::write(const char* buffer, unsigned int size)
{
    return LinuxSocketCommon::write(
        socket_fd,
        buffer,
        size,
        blocking_timeout,
        ts_blocking_timeout,
        reinterpret_cast<sockaddr*>(&output_interface),
        sizeof(sockaddr_ll));
}

//====================================================================
// Clears socket of any received data
//====================================================================
void LinuxRawSocket::clearBuffer()
{
    LinuxSocketCommon::clearBuffer(
        socket_fd,
        reinterpret_cast<sockaddr*>(&input_interface),
        sizeof(sockaddr_ll));
}

//====================================================================
// Retrieves the interface index of a specified index
//====================================================================
int LinuxRawSocket::getInterfaceIndex(const std::string& interface_name)
{
    // Fill out an ifreq with name of desired interface
    ifreq iface;
    strcpy(iface.ifr_name, interface_name.c_str());

    // Request the corresponding interface number
    ioctl(socket_fd, SIOCGIFINDEX, &iface);

    // Return interface #
    return iface.ifr_ifindex;
}

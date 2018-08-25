#include <cstdio>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netdb.h>
#include <poll.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "LinuxRawSocketImpl.hpp"

#include "PosixSocketCommon.hpp"
#include "PosixTimespec.hpp"

//==============================================================================
// Creates a Linux raw socket
//==============================================================================
LinuxRawSocketImpl::LinuxRawSocketImpl() :
    blocking_timeout(0.0)
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

    // Create the socket; third argument specifies which Ethernet protocols are
    // received, current setting is all
    socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if (socket_fd == -1)
    {
        throw std::runtime_error(strerror(errno));
    }
}

//==============================================================================
// Shuts this socket down
//==============================================================================
LinuxRawSocketImpl::~LinuxRawSocketImpl()
{
    PosixSocketCommon::shutdown(socket_fd);
}

//==============================================================================
// Enables blocking
//==============================================================================
bool LinuxRawSocketImpl::enableBlocking()
{
    return PosixSocketCommon::enableBlocking(socket_fd);
}

//==============================================================================
// Disables blocking
//==============================================================================
bool LinuxRawSocketImpl::disableBlocking()
{
    return PosixSocketCommon::disableBlocking(socket_fd);
}

//==============================================================================
// Returns blocking status
//==============================================================================
bool LinuxRawSocketImpl::isBlockingEnabled()
{
    return PosixSocketCommon::isBlockingEnabled(socket_fd);
}

//==============================================================================
// Sets the interface this socket will get data from
//==============================================================================
bool LinuxRawSocketImpl::setInputInterface(const std::string& interface_name)
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
#if defined DEBUG
        perror("LinuxRawSocketImpl::setInputInterface");
#endif
        return false;
    }

    return true;
}

//==============================================================================
// Set the interface this socket will send data to
//==============================================================================
bool LinuxRawSocketImpl::setOutputInterface(const std::string& interface_name)
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

//==============================================================================
// Reads data from socket into buffer
//==============================================================================
int LinuxRawSocketImpl::read(unsigned char* buffer, unsigned int size)
{
    return PosixSocketCommon::read(
        socket_fd,
        buffer,
        size,
        blocking_timeout,
        reinterpret_cast<sockaddr*>(&input_interface),
        sizeof(sockaddr_ll));
}

//==============================================================================
// Writes data to socket
//==============================================================================
int LinuxRawSocketImpl::write(const unsigned char* buffer, unsigned int size)
{
    return PosixSocketCommon::write(
        socket_fd,
        buffer,
        size,
        blocking_timeout,
        reinterpret_cast<sockaddr*>(&output_interface),
        sizeof(sockaddr_ll));
}

//==============================================================================
// Clears socket of any received data
//==============================================================================
void LinuxRawSocketImpl::clearBuffer()
{
    PosixSocketCommon::clearBuffer(
        socket_fd,
        reinterpret_cast<sockaddr*>(&input_interface),
        sizeof(sockaddr_ll));
}

//==============================================================================
// Retrieves the interface index of a specified index
//==============================================================================
int LinuxRawSocketImpl::getInterfaceIndex(const std::string& interface_name)
{
    // Fill out an ifreq with name of desired interface
    ifreq iface;
    strcpy(iface.ifr_name, interface_name.c_str());

    // Request the corresponding interface number
    ioctl(socket_fd, SIOCGIFINDEX, &iface);

    // Return interface #
    return iface.ifr_ifindex;
}

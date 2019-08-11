#include <WS2tcpip.h>
#include <WinSock2.h>
#include <cmath>
#include <cstdint>
#include <sstream>
#include <stdio.h>
#include <string>

#if defined DEBUG
#include <iostream>
#endif

#include "WindowsSocketCommon.hpp"

//=============================================================================
bool WindowsSocketCommon::enableBlocking(SOCKET socket_fd,
                                         bool&  is_blocking)
{
    // Set what blocking mode to set the socket to
    u_long mode = 0;

    // Actually perform the file descriptor mod
    if (ioctlsocket(socket_fd, FIONBIO, &mode) != NO_ERROR)
    {
        printErrorMessage("WindowsSocketCommon::enableBlocking");
        return false;
    }

    // Track the blocking status
    is_blocking = true;

    return true;
}

//=============================================================================
bool WindowsSocketCommon::disableBlocking(SOCKET socket_fd,
                                          bool&  is_blocking)
{
    // Set what blocking mode to set the socket to
    u_long mode = 1;

    // Actually perform the file descriptor mod
    if (ioctlsocket(socket_fd, FIONBIO, &mode) != NO_ERROR)
    {
        printErrorMessage("WindowsSocketCommon::disableBlocking");
        return false;
    }

    // Track the blocking status
    is_blocking = false;

    return true;
}

//=============================================================================
void WindowsSocketCommon::setBlockingTimeout(double  blocking_timeout,
                                             double& class_bt,
                                             INT&    class_ts_bt)
{
    // Timeouts of less than or equal to 0 disable the timeout
    if (blocking_timeout <= 0.0)
    {
        class_bt = -1.0;
        return;
    }

    // Store the user-given timeout
    class_bt = blocking_timeout;

    // Convert given blocking_timeout to stored form
    class_ts_bt = static_cast<INT>(blocking_timeout * 1e3);
}

//=============================================================================
int WindowsSocketCommon::doBlockingTimeout(SOCKET socket_fd,
                                           short  events,
                                           INT&   class_ts_bt)
{
    // Fill out the structure describing poll parameters
    WSAPOLLFD polldata;
    polldata.fd = socket_fd;
    polldata.events = events;

    int ready_count = WSAPoll(&polldata, 1, class_ts_bt);

    if (ready_count == SOCKET_ERROR)
    {
        printErrorMessage("WindowsSocketCommon::doBlockingTimeout");
    }

    return ready_count;
}

//=============================================================================
bool WindowsSocketCommon::bind(SOCKET        socket_fd,
                               unsigned int& port,
                               int           socktype,
                               int           protocol,
                               sockaddr_in&  class_la)
{
    // Convert int local_port to string
    std::string port_s;
    std::ostringstream ostream;
    ostream << port;
    port_s = ostream.str();

    // Define connection properties of this socket; IPv4 only for now
    addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = socktype;
    hints.ai_protocol = protocol;
    hints.ai_flags    = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    addrinfo* result = NULL;
    int ret = getaddrinfo(NULL, port_s.c_str(), &hints, &result);
    if (ret != 0)
    {
        WindowsSocketCommon::printErrorMessage("WindowsSocketCommon::bind");
        return false;
    }

    // Copy the first address resolved into its own storage
    memcpy(&class_la, result->ai_addr, sizeof(sockaddr_in));

    // Free the rest of the address list
    freeaddrinfo(result);

    // Bind the socket
    if (::bind(socket_fd,
               reinterpret_cast<sockaddr*>(&class_la),
               sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        WindowsSocketCommon::printErrorMessage("WindowsSocketCommon::bind");
        return false;
    }

    return true;
}

//=============================================================================
int WindowsSocketCommon::read(SOCKET        socket_fd,
                              std::uint8_t* buffer,
                              unsigned int  size,
                              double        class_bt,
                              INT&          class_ts_bt,
                              sockaddr*     class_rfa,
                              int           class_rfa_size,
                              bool          class_ba)
{
    // Is a valid timeout set?
    if (class_ba && class_bt > 0.0)
    {
        if (doBlockingTimeout(socket_fd, POLLRDNORM, class_ts_bt) == 0)
        {
            // No data is available to read, so return before attempting to read
            // for real
            return 0;
        }
    }

    // Do the read
    int bytes_read = recvfrom(socket_fd,
                              reinterpret_cast<char*>(buffer),
                              size,
                              0,
                              class_rfa,
                              &class_rfa_size);

    // Check for errors
    if (bytes_read == SOCKET_ERROR)
    {
        // Retrieve the error code
        int last_error = WSAGetLastError();

        // If the error was that this read would have blocked, don't call that
        // an error, just return 0
        if (last_error == WSAEWOULDBLOCK)
        {
            return 0;
        }

        printErrorMessage("WindowsSocketCommon::read");
    }

    return bytes_read;
}

//=============================================================================
int WindowsSocketCommon::write(SOCKET              socket_fd,
                               const std::uint8_t* buffer,
                               unsigned int        size,
                               double              class_bt,
                               INT&                class_ts_bt,
                               sockaddr*           class_sta,
                               int                 class_sta_size,
                               bool                class_ba)
{
    // Is a valid timeout set?
    if (class_ba && class_bt > 0.0)
    {
        if (doBlockingTimeout(socket_fd, POLLWRNORM, class_ts_bt) == 0)
        {
            // Writing now would block, so return before actually attempting the
            // write
            return 0;
        }
    }

    // Perform the write
    int bytes_written = sendto(socket_fd,
                               reinterpret_cast<const char*>(buffer),
                               size,
                               0,
                               class_sta,
                               class_sta_size);

    // Check for errors
    if (bytes_written == SOCKET_ERROR)
    {
        printErrorMessage("WindowsSocketCommon::write");
    }

    return bytes_written;
}

//=============================================================================
void WindowsSocketCommon::clearBuffer(SOCKET    socket_fd,
                                      sockaddr* class_rfa,
                                      int       class_rfa_size,
                                      bool      class_ba)
{
    // Save blocking status; will set back after reading
    bool now_blocking = class_ba;

    disableBlocking(socket_fd, class_ba);

    // Data will be discarded into here when copied out of the socket.
    uint8_t buf;

    // Create a temporary timeout to give to read
    INT temp_timeout = 0;

    // Read single bytes until no more remain
    while(read(socket_fd,
               &buf,
               1,
               -1,
               temp_timeout,
               class_rfa,
               class_rfa_size,
               class_ba) > 0)
    {
    }

    // Set blocking status back to what it was
    if (now_blocking)
    {
        enableBlocking(socket_fd, class_ba);
    }
    else
    {
        disableBlocking(socket_fd, class_ba);
    }
}

//=============================================================================
void WindowsSocketCommon::shutdown(SOCKET socket_fd)
{
    // Shutdown the send half of the connection
    ::shutdown(socket_fd, SD_BOTH);

    // Close the file descriptor
    closesocket(socket_fd);
}

//=============================================================================
void WindowsSocketCommon::printErrorMessage(const std::string& location)
{
#if defined DEBUG
    // Will point to a wchar buffer containing the error string after the call
    // to FormatMessage
    LPTSTR error_string = 0;

    // Fill in error_string with the last socket error
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  WSAGetLastError(),
                  LANG_SYSTEM_DEFAULT,
                  error_string,
                  0,
                  NULL);

    // Print the error message
    std::cerr << location << ": ";
    fwprintf(stderr, "%s", error_string);

    // Free the string created by FormatMessage
    LocalFree(error_string);
#endif
}

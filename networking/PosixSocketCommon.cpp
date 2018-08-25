// Common POSIX socket operations live here

#include <cmath>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "PosixSocketCommon.hpp"

//==============================================================================
// Enables blocking on a file descriptor
//==============================================================================
bool PosixSocketCommon::enableBlocking(int socket_fd)
{
    // Get current file status
    int fd_stat = fcntl(socket_fd, F_GETFL);

    // Enable blocking
    if (fcntl(socket_fd, F_SETFL, fd_stat & ~O_NONBLOCK) != 0)
    {
#if defined DEBUG
        perror("PosixSocketCommon::enableBlocking");
#endif
        return false;
    }

    return true;
}

//==============================================================================
// Disables blocking on a file descriptor
//==============================================================================
bool PosixSocketCommon::disableBlocking(int socket_fd)
{
    // Get current file status
    int fd_stat = fcntl(socket_fd, F_GETFL);

    // Disable blocking and check for errors
    if (fcntl(socket_fd, F_SETFL, fd_stat | O_NONBLOCK) != 0)
    {
#if defined DEBUG
        perror("PosixSocketCommon::disableBlocking");
#endif
        return false;
    }

    return true;
}

//==============================================================================
// Returns true if the given file descriptor can block, false otherwise
//==============================================================================
bool PosixSocketCommon::isBlockingEnabled(int socket_fd)
{
    return (fcntl(socket_fd, F_GETFL) & O_NONBLOCK) == 0;
}

//==============================================================================
// Performs a blocking timeout
//==============================================================================
int PosixSocketCommon::doBlockingTimeout(int    socket_fd,
                                         short  events,
                                         double class_ts_bt)
{
    // Set up the poll structure
    pollfd polldata;
    polldata.fd = socket_fd;
    polldata.events = events;

    // Perform the poll, third argument is given in milliseconds
    int ready_count = poll(&polldata, 1, class_ts_bt * 1000);

#if defined DEBUG
    if (ready_count == -1)
    {
        // A poll error occurred, report it
        perror("PosixSocketCommon::doBlockingTimeout");
    }
#endif

    return ready_count;
}

//==============================================================================
// Associates socket with a local address
//==============================================================================
bool PosixSocketCommon::bind(int           socket_fd,
                             sockaddr_in&  local_address,
                             unsigned int& port)
{
    socklen_t local_address_len = sizeof(sockaddr_in);

    // Set up local address info to bind with
    local_address.sin_family      = AF_INET;
    local_address.sin_port        = htons(port);
    local_address.sin_addr.s_addr = 0;

    // Do the bind
    if (::bind(socket_fd,
               reinterpret_cast<sockaddr*>(&local_address),
               local_address_len) == -1)
    {
#if defined DEBUG
        perror("PosixSocketCommon::bind");
#endif
        return false;
    }

    if (getsockname(socket_fd,
                    reinterpret_cast<sockaddr*>(&local_address),
                    &local_address_len) == -1)
    {
#if defined DEBUG
        perror("PosixSocketCommon::bind");
#endif

        return false;
    }

    // Tell the user the port they got
    port = ntohs(local_address.sin_port);

    return true;
}

//==============================================================================
// Reads socket data into buffer
//==============================================================================
int PosixSocketCommon::read(int            socket_fd,
                            unsigned char* buffer,
                            unsigned int   size,
                            double         class_ts_bt,
                            sockaddr*      class_rfa,
                            socklen_t      class_rfa_size)
{
    // Is a valid timeout set?
    if (isBlockingEnabled(socket_fd) && class_ts_bt > 0.0)
    {
        // Perform the blocking timeout and check if the POLLIN event occurred
        if (doBlockingTimeout(socket_fd, POLLIN, class_ts_bt) == 0)
        {
            // No data is ready to read, just return
            return 0;
        }
    }

    // Read data
    int ret = recvfrom(socket_fd, buffer, size, 0, class_rfa, &class_rfa_size);

#if defined DEBUG
    if (ret == -1)
    {
        perror("PosixSocketCommon::read");
    }
#endif

    return ret;
}

//==============================================================================
// Writes buffer data into socket
//==============================================================================
int PosixSocketCommon::write(int                  socket_fd,
                             const unsigned char* buffer,
                             unsigned int         size,
                             double               class_ts_bt,
                             sockaddr*            class_sta,
                             socklen_t            class_sta_size)
{
    // Is a valid timeout set?
    if (isBlockingEnabled(socket_fd) && class_ts_bt > 0.0)
    {
        // Perform the blocking timeout and check if the POLLOUT event occurred
        if (doBlockingTimeout(socket_fd, POLLOUT, class_ts_bt) == 0)
        {
            // No data is ready to read, just return
            return 0;
        }
    }

    // Write data
    int ret = sendto(socket_fd, buffer, size, 0, class_sta, class_sta_size);

#if defined DEBUG
    if (ret == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
    {
        perror("PosixSocketCommon::write");
    }
#endif

    return ret;
}

//==============================================================================
// Clears all data out of a socket's receive buffer
//==============================================================================
void PosixSocketCommon::clearBuffer(int       socket_fd,
                                    sockaddr* class_rfa,
                                    socklen_t class_rfa_size)
{
    // Interested if data is available
    pollfd polldata;
    polldata.fd = socket_fd;
    polldata.events = POLLIN;

    unsigned char buf;

    while(true)
    {
        // Poll the socket and see if there is data
        if (poll(&polldata, 1, 0) == -1)
        {
#if defined DEBUG
            perror("PosixSocketCommon::clearBuffer");
#endif
            return;
        }

        // If no data available, leave
        if (polldata.revents == 0)
        {
            return;
        }

        // Read a byte, leave if error
        if (read(socket_fd, &buf, 1, 0, class_rfa, class_rfa_size) < 1)
        {
            return;
        }
    }
}

//==============================================================================
// Shuts the given socket down
//==============================================================================
void PosixSocketCommon::shutdown(int socket_fd)
{
    // Stop reception and transmission on the socket
    ::shutdown(socket_fd, SHUT_RDWR);

    // Close the socket file descriptor
    close(socket_fd);
}

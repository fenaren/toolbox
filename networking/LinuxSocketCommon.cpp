// Common Linux socket operations live here

#include <cmath>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "LinuxSocketCommon.hpp"

//====================================================================
// Enables blocking on a file descriptor
//====================================================================
bool LinuxSocketCommon::enableBlocking(int socket_fd)
{
    // Get current file status
    int fd_stat = fcntl(socket_fd, F_GETFL);

    // Enable blocking
    if (fcntl(socket_fd, F_SETFL, fd_stat & ~O_NONBLOCK) != 0)
    {
        perror("LinuxSocketCommon::enableBlocking");
        return false;
    }

    return true;
}

//====================================================================
// Disables blocking on a file descriptor
//====================================================================
bool LinuxSocketCommon::disableBlocking(int socket_fd)
{
    // Get current file status
    int fd_stat = fcntl(socket_fd, F_GETFL);

    // Disable blocking and check for errors
    if (fcntl(socket_fd, F_SETFL, fd_stat | O_NONBLOCK) != 0)
    {
        perror("LinuxSocketCommon::disableBlocking");
        return false;
    }

    return true;
}

//====================================================================
// Returns true if the given file descriptor can block, false otherwise
//====================================================================
bool LinuxSocketCommon::isBlockingEnabled(int socket_fd)
{
    return (fcntl(socket_fd, F_GETFL) & O_NONBLOCK) == 0;
}

//====================================================================
// Sets blocking timeout parameters appropriately
//====================================================================
void LinuxSocketCommon::setBlockingTimeout(double    blocking_timeout,
                                           double&   class_bt,
                                           timespec& class_ts_bt)
{
    // Timeout values less than or equal to 0 disable the timeout
    if (blocking_timeout <= 0.0)
    {
        class_bt = -1.0;
        return;
    }

    // Save the user-specified timeout
    class_bt = blocking_timeout;

    // Fill in the timespec structure with the specified timeout.
    class_ts_bt.tv_sec = floor(blocking_timeout);
    class_ts_bt.tv_nsec = (blocking_timeout - class_ts_bt.tv_sec) * 1e9;
}

//====================================================================
// Performs a blocking timeout
//====================================================================
int LinuxSocketCommon::doBlockingTimeout(int       socket_fd,
                                         short     events,
                                         timespec& class_ts_bt)
{
    // Set up the poll structure
    pollfd polldata;
    polldata.fd = socket_fd;
    polldata.events = events;

    // Perform the poll
    int ready_count = ppoll(&polldata, 1, &class_ts_bt, 0);

    // Handle errors
    if (ready_count == -1)
    {
        // A poll error occurred, report it
        perror("LinuxSocketCommon::doBlockingTimeout");
    }

    return ready_count;
}

//====================================================================
// Reads socket data into buffer
//====================================================================
int LinuxSocketCommon::read(int          socket_fd,
                            char*        buffer,
                            unsigned int size,
                            double       class_bt,
                            timespec&    class_ts_bt,
                            sockaddr*    class_rfa,
                            socklen_t    class_rfa_size)
{
    // Is a valid timeout set?
    if (isBlockingEnabled(socket_fd) && class_bt > 0.0)
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

    // Check for errors
    if (ret == -1)
    {
        perror("LinuxSocketCommon::read");
    }

    return ret;
}

//====================================================================
// Writes buffer data into socket
//====================================================================
int LinuxSocketCommon::write(int          socket_fd,
                             const char*  buffer,
                             unsigned int size,
                             double       class_bt,
                             timespec&    class_ts_bt,
                             sockaddr*    class_sta,
                             socklen_t    class_sta_size)
{
    // Is a valid timeout set?
    if (isBlockingEnabled(socket_fd) && class_bt > 0.0)
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

    // Check for errors
    if (ret == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
    {
        perror("LinuxSocketCommon::write");
    }

    return ret;
}

//====================================================================
// Clears all data out of a socket's receive buffer
//====================================================================
void LinuxSocketCommon::clearBuffer(int       socket_fd,
                                    sockaddr* class_rfa,
                                    socklen_t class_rfa_size)
{
    // Interested if data is available
    pollfd polldata;
    polldata.fd = socket_fd;
    polldata.events = POLLIN;

    char buf;

    while(true)
    {
        // Poll the socket and see if there is data
        if (poll(&polldata, 1, 0) == -1)
        {
            perror("LinuxSocketCommon::clearBuffer");
            return;
        }

        // If no data available, leave
        if (polldata.revents == 0)
        {
            return;
        }

        // Create a temporary timespec to satisfy read
        timespec temp_timespec;
        temp_timespec.tv_sec  = 0;
        temp_timespec.tv_nsec = 0;

        // Read a byte, leave if error
        if (read(socket_fd,
                 &buf,
                 1,
                 -1,
                 temp_timespec,
                 class_rfa,
                 class_rfa_size) < 1)
        {
            return;
        }
    }
}

//====================================================================
// Shuts the given socket down
//====================================================================
void LinuxSocketCommon::shutdown(int socket_fd)
{
    // Stop reception and transmission on the socket
    shutdown(socket_fd, SHUT_RDWR);

    // Close the socket file descriptor
    close(socket_fd);
}

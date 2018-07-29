// Common POSIX socket operations live here

#include <sys/socket.h>
#include <sys/types.h>

namespace PosixSocketCommon
{
    // Enables blocking on reads and writes using the specified file descriptor.
    bool enableBlocking(int socket_fd);

    // Disables blocking on reads and writes using the specified file
    // descriptor.
    bool disableBlocking(int socket_fd);

    // Returns true when reads and writes using the given file descriptor can
    // block, false otherwise.
    bool isBlockingEnabled(int socket_fd);

    // Performs a blocking timeout on the given file descriptor.  The block
    // lasts until the events described by 'events' occur, or when the duration
    // of time (seconds) represented by 'class_ts_bt' has passed.
    int doBlockingTimeout(int socket_fd, short events, double class_ts_bt);

    // Associates a name and a port with a newly-created socket
    bool bind(int socket_fd, sockaddr_in& local_address, unsigned int& port);

    // Reads from the given file descriptor, being careful to conduct a blocking
    // timeout beforehand if instructed to.  A blocking timeout is performed if
    // 'class_ts_bt' (seconds) represents a positive durations of time.
    // 'class_rfa' and 'class_rfa_size' vary in purpose depending on the type of
    // socket being dealt with.  When used with packet-based sockets,
    // 'class_rfa' is a buffer into which the address of the sender is written.
    // When used with raw sockets, 'class_rfa' is a buffer containing
    // information about the interface to read from.  In both cases,
    // 'class_rfa_size' is the length of the 'class_rfa' buffer, in bytes.
    int read(int          socket_fd,
             char*        buffer,
             unsigned int size,
             double       class_ts_bt,
             sockaddr*    class_rfa,
             socklen_t    class_rfa_size);

    // Writes to the given file descriptor, being careful to conduct a blocking
    // timeout beforehand if instructed to.  A blocking timeout is performed if
    // 'class_ts_bt' (seconds) represents a positive durations of time.
    // 'class_sta' and 'class_sta_size' vary in purpose depending on the type of
    // socket being dealt with.  When used with packet-based sockets,
    // 'class_sta' is the address of the destination the data being written is
    // to be sent to.  When use with raw sockets, 'class_sta' is the interface
    // to output the data on.  In both cases, 'class_sta_size' represents the
    // size of the 'class_rfa' buffer, in bytes.
    int write(int          socket_fd,
              const char*  buffer,
              unsigned int size,
              double       class_ts_bt,
              sockaddr*    class_sta,
              socklen_t    class_sta_size);

    // Clears the receive buffer of the specified socket.  It does this by
    // iteratively reading single bytes of data from the socket until it would
    // block.  See the above documentation of the 'read' function for
    // explanations of the 'class_rfa' and 'class_rfa_size' parameters.
    void clearBuffer(int       socket_fd,
                     sockaddr* class_rfa,
                     socklen_t class_rfa_size);

    // Shuts the given socket down.  First traffic is stopped, then the file
    // descriptor is closed.
    void shutdown(int socket_fd);
}

// Common Windows socket operations live here

#if !defined WINDOWS_SOCKET_COMMON_HPP
#define WINDOWS_SOCKET_COMMON_HPP

#include <WinSock2.h>
#include <string>

namespace WindowsSocketCommon
{
    // Enables blocking on reads and writes using the specified file descriptor.
    bool enableBlocking(SOCKET socket_fd, bool& is_blocking);

    // Disables blocking on reads and writes using the specified file descriptor.
    bool disableBlocking(SOCKET socket_fd, bool& is_blocking);

    // Sets class_bt and class_ts_bt based on blocking_timeout (a duration in
    // seconds).
    void setBlockingTimeout(double  blocking_timeout,
                            double& class_bt,
                            INT&    class_ts_bt);

    // Performs a blocking timeout on the given file descriptor.  The block lasts
    // until the events described by 'events' occur, or when the duration of time
    // represented by 'class_ts_bt' has passed.
    int doBlockingTimeout(SOCKET socket_fd, short events, INT& class_ts_bt);

    // Associates the given socket with a given port number ("names" the socket).
    // 'socktype' and 'protocol' are set according to the type of socket being
    // bound.  'class_la' is filled in with the local address that was bound to.
    // Returns true on success, false otherwise.
    bool bind(SOCKET       socked_fd,
              unsigned int port,
              int          socktype,
              int          protocol,
              sockaddr_in& class_la);

    // Reads from the given file descriptor, being careful to conduct a blocking
    // timeout beforehand if instructed to.  A blocking timeout is performed if
    // 'class_bt' and 'class_ts_bt' represent positive durations of time.
    // 'class_rfa' and 'class_rfa_size' vary in purpose depending on the type of
    // socket being dealt with.  When used with packet-based sockets, 'class_rfa'
    // is a buffer into which the address of the sender is written.  When used
    // with raw sockets, 'class_rfa' is a buffer containing information about the
    // interface to read from.  In both cases, 'class_rfa_size' is the length of
    // the 'class_rfa' buffer, in bytes.  'class_ba' should be set true if
    // blocking is enabled on the socket, false otherwise.
    int read(SOCKET       socket_fd,
             char*        buffer,
             unsigned int size,
             double       class_bt,
             INT&         class_ts_bt,
             sockaddr*    class_rfa,
             int          class_rfa_size,
             bool         class_ba);

    // Writes to the given file descriptor, being careful to conduct a blocking
    // timeout beforehand if instructed to.  A blocking timeout is performed if
    // 'class_bt' and 'class_ts_bt' represent positive durations of time.
    // 'class_sta' and 'class_sta_size' vary in purpose depending on the type of
    // socket being dealt with.  When used with packet-based sockets, 'class_sta'
    // is the address of the destination the data being written is to be sent to.
    // When use with raw sockets, 'class_sta' is the interface to output the data
    // on.  In both cases, 'class_sta_size' represents the size of the 'class_rfa'
    // buffer, in bytes.  'class_ba' should be set true if blocking is enabled on
    // the socket, false otherwise.
    int write(SOCKET       socket_fd,
              const char*  buffer,
              unsigned int size,
              double       class_bt,
              INT&         class_ts_bt,
              sockaddr*    class_sta,
              int          class_sta_size,
              bool         class_ba);

    // Clears the receive buffer of the specified socket.  It does this by
    // iteratively reading single bytes of data from the socket until it would
    // block.  See the above documentation of the 'read' function for explanations
    // of the 'class_rfa' and 'class_rfa_size' parameters.  'class_ba' should be
    // set true if blocking is enabled on the socket, false otherwise.
    void clearBuffer(SOCKET    socket_fd,
                     sockaddr* class_rfa,
                     int       class_rfa_size,
                     bool      class_ba);

    // Shuts the given socket down.  First traffic is stopped, then the file
    // descriptor is closed.
    void shutdown(SOCKET socket_fd);

    // When handling error conditions, this function can be used to display the
    // location where the error occurred, as well as a string description of the
    // error.
    void printErrorMessage(const std::string& function_name);
}

#endif

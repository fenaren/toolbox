// Leigh Garbs

#include "WindowsTCPSocketImpl.hpp"

#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "WindowsSocketCommon.hpp"

//=============================================================================
// Creates the socket
//=============================================================================
WindowsTCPSocketImpl::WindowsTCPSocketImpl() :
    TCPSocketImpl(),
    is_blocking(false)
{
  // Initialize the addresses we're tracking
  memset(&local_address,  0, sizeof(sockaddr_in));
  memset(&peer_address,   0, sizeof(sockaddr_in));

  blocking_timeout = -1.0;
  ts_blocking_timeout = 0;

  // Initialize the Windows socket driver
  WSADATA wsaData;
  int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0)
  {
    WindowsSocketCommon::printErrorMessage(
      "WindowsTCPSocketImpl::WindowsTCPSocketImpl");
    return;
  }

  // Create the socket
  socket_fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // Check for socket creation errors
  if (socket_fd == INVALID_SOCKET)
  {
    WindowsSocketCommon::printErrorMessage(
      "WindowsTCPSocketImpl::WindowsTCPSocketImpl");
    return;
  }
}

//=============================================================================
// Sets a couple things for an already-initialized socket descriptor
//=============================================================================
WindowsTCPSocketImpl::WindowsTCPSocketImpl(SOCKET       socket_fd,
                                           sockaddr_in& local_address,
                                           sockaddr_in& peer_address) :
  TCPSocketImpl()
{
  // Copy the given socket descriptor
  this->socket_fd = socket_fd;

  // Copy the saved addresses from the other socket
  memcpy(&this->local_address,  &local_address,  sizeof(sockaddr_in));
  memcpy(&this->peer_address,   &peer_address, sizeof(sockaddr_in));
}

//=============================================================================
// Closes and destroys the socket
//=============================================================================
WindowsTCPSocketImpl::~WindowsTCPSocketImpl()
{
  WindowsSocketCommon::shutdown(socket_fd);
}

//=============================================================================
// Enables blocking
//=============================================================================
bool WindowsTCPSocketImpl::enableBlocking()
{
  return WindowsSocketCommon::enableBlocking(socket_fd, is_blocking);
}

//=============================================================================
// Disables blocking
//=============================================================================
bool WindowsTCPSocketImpl::disableBlocking()
{
  return WindowsSocketCommon::disableBlocking(socket_fd, is_blocking);
}

//=============================================================================
// Returns whether or not this socket blocks
//=============================================================================
bool WindowsTCPSocketImpl::isBlockingEnabled()
{
  return is_blocking;
}

//=============================================================================
// Sets the blocking timeout
//=============================================================================
void WindowsTCPSocketImpl::setBlockingTimeout(double blocking_timeout)
{
  WindowsSocketCommon::setBlockingTimeout(blocking_timeout,
                                          this->blocking_timeout,
                                          ts_blocking_timeout);
}

//=============================================================================
// Gets the blocking timeout
//=============================================================================
double WindowsTCPSocketImpl::getBlockingTimeout() const
{
  return blocking_timeout;
}

//=============================================================================
// Associates this socket with a name and a port
//=============================================================================
bool WindowsTCPSocketImpl::bind(unsigned int port)
{
  return WindowsSocketCommon::bind(socket_fd,
                                   port,
                                   SOCK_STREAM,
                                   IPPROTO_TCP,
                                   local_address);
}

//=============================================================================
// Instructs this socket to begin listening for incoming traffic
//=============================================================================
bool WindowsTCPSocketImpl::listen()
{
  // Do the listen
  if (::listen(socket_fd, 1) == SOCKET_ERROR)
  {
    WindowsSocketCommon::printErrorMessage("WindowsTCPSocketImpl::listen");
    return false;
  }

  return true;
}

//=============================================================================
// Accepts any pending incoming connections
//=============================================================================
WindowsTCPSocketImpl* WindowsTCPSocketImpl::accept(bool take_over)
{
  // Is a valid timeout set?
  if (isBlockingEnabled() && blocking_timeout > 0.0)
  {
    if (WindowsSocketCommon::doBlockingTimeout(socket_fd,
                                               POLLRDNORM,
                                               ts_blocking_timeout) == 0)
    {
      // No data is available to read, so return before attempting to read for
      // real
      return 0;
    }
  }

  // Accept requires an integer address containing sockaddr_in size
  int sockaddr_in_size = sizeof(sockaddr_in);

  // Accept an incoming connection; will block if blocking is enabled
  SOCKET socket_fd_new = ::accept(socket_fd,
                                  reinterpret_cast<sockaddr*>(&peer_address),
                                  &sockaddr_in_size);

  // Check for errors
  if (socket_fd_new == INVALID_SOCKET)
  {
    // Get the error code corresponding to whatever happened
    int last_error = WSAGetLastError();

    // If the socket was marked non-blocking and accept would have blocked
    // otherwise, immediately return
    if (last_error == WSAEWOULDBLOCK)
    {
        return 0;
    }

    // Report the error and shutdown
    WindowsSocketCommon::printErrorMessage("WindowsTCPSocketImpl::accept");
    return 0;
  }

  // Shutdown the current socket file descriptor and start using the new one,
  // if that's what the user wants
  if (take_over)
  {
    // First, shut down the old listening connection
    WindowsSocketCommon::shutdown(socket_fd);

    // Start using the new one
    socket_fd = socket_fd_new;

    // Set the blocking status of this new socket to whatever the old socket
    // was set to
    if (is_blocking)
    {
      enableBlocking();
    }
    else
    {
      disableBlocking();
    }

    return this;
  }

  // Create a new socket associated with the newly-accepted connection
  return new WindowsTCPSocketImpl(socket_fd_new,
                                  local_address,
                                  peer_address);
}

//=============================================================================
// Connects this socket to another socket
//=============================================================================
bool WindowsTCPSocketImpl::connect(const std::string& hostname,
                                   unsigned int       port)
{
  // Convert int remote_port to string
  std::string port_s;
  std::ostringstream ostream;
  ostream << port;
  port_s = ostream.str();

  // Describe what kind of peer socket we're looking for
  addrinfo hints;
  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family   = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  // Resolve the local address and port to be used by the server
  addrinfo* result = NULL;
  int ret = getaddrinfo(hostname.c_str(), port_s.c_str(), &hints, &result);
  if (ret != 0)
  {
    WindowsSocketCommon::printErrorMessage("WindowsTCPSocketImpl::connect");
    return false;
  }

  // Save the remote address
  memcpy(&peer_address, result->ai_addr, sizeof(sockaddr_in));

  // Attempt to connect to whatever peer was found above
  if (::connect(socket_fd,
                result->ai_addr,
                result->ai_addrlen) == SOCKET_ERROR)
  {
    WindowsSocketCommon::printErrorMessage("WindowsTCPSocketImpl::connect");
    return false;
  }

  return true;
}

//=============================================================================
// Returns whether or not this socket is connected to another
//=============================================================================
bool WindowsTCPSocketImpl::isConnected()
{
  // Store current blocking status
  bool blocking = isBlockingEnabled();

  disableBlocking();

  // See what happens if a single byte is read
  char buf;
  int ret = recv(socket_fd, &buf, 1, MSG_PEEK);

  // Re-enable blocking if the socket was previously blocking
  if (blocking)
  {
    enableBlocking();
  }

  // If the previous read returned 0, the peer performed an orderly shutdown and
  // the socket is therefore not connected.  Besides that case, if the read
  // results in an WSAENOTCONN error, this also obviously means the socket is not
  // connected.  Consider the socket connected in any other case.
  return !(ret == 0 || (ret == SOCKET_ERROR && WSAGetLastError() == WSAENOTCONN));
}

//=============================================================================
// Reads data from this socket into user code
//=============================================================================
int WindowsTCPSocketImpl::read(char* buffer, unsigned int size)
{
  return WindowsSocketCommon::read(
    socket_fd,
    buffer,
    size,
    blocking_timeout,
    ts_blocking_timeout,
    reinterpret_cast<sockaddr*>(&peer_address),
    sizeof(sockaddr_in),
    is_blocking);
}

//=============================================================================
// Writes data from user code into this socket
//=============================================================================
int WindowsTCPSocketImpl::write(const char* buffer, unsigned int size)
{
  return WindowsSocketCommon::write(socket_fd,
                                    buffer,
                                    size,
                                    blocking_timeout,
                                    ts_blocking_timeout,
                                    0,
                                    0,
                                    is_blocking);
}

//=============================================================================
// Establishes where packets from this socket will be sent
//=============================================================================
void WindowsTCPSocketImpl::clearBuffer()
{
  WindowsSocketCommon::clearBuffer(
    socket_fd,
    reinterpret_cast<sockaddr*>(&peer_address),
    sizeof(sockaddr_in),
    is_blocking);
}

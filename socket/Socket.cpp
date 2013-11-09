// Leigh Garbs

#include "Socket.hpp"

#include <string>

#include "SocketImpl.hpp"

//=============================================================================
// Does nothing
//=============================================================================
Socket::Socket()
{
}

//=============================================================================
// Does nothing
//=============================================================================
Socket::~Socket()
{
}

//=============================================================================
// Calls implementation-specific enableBlocking
//=============================================================================
bool Socket::enableBlocking()
{
  if (socket_impl)
  {
    return socket_impl->enableBlocking();
  }

  return false;
}

//=============================================================================
// Calls implementation-specific disableBlocking
//=============================================================================
bool Socket::disableBlocking()
{
  if (socket_impl)
  {
    return socket_impl->disableBlocking();
  }

  return false;
}

//=============================================================================
// Calls implementation-specific isBlocking
//=============================================================================
bool Socket::isBlockingEnabled()
{
  if (socket_impl)
  {
    return socket_impl->isBlockingEnabled();
  }

  return false;
}

//=============================================================================
// Calls implementation-specific setBlockingTimeout
//=============================================================================
void Socket::setBlockingTimeout(double blocking_timeout)
{
  if (socket_impl)
  {
    return socket_impl->setBlockingTimeout(blocking_timeout);
  }
}

//=============================================================================
// Calls implementation-specific getBlockingTimeout
//=============================================================================
double Socket::getBlockingTimeout() const
{
  if (socket_impl)
  {
    return socket_impl->getBlockingTimeout();
  }

  return 0.0;
}

//=============================================================================
// Calls implementation-specific read
//=============================================================================
int Socket::read(char* buffer, unsigned int size)
{
  if (socket_impl)
  {
    return socket_impl->read(buffer, size);
  }

  return -1;
}

//=============================================================================
// Calls implementation-specific write
//=============================================================================
int Socket::write(const char* buffer, unsigned int size)
{
  if (socket_impl)
  {
    return socket_impl->write(buffer, size);
  }

  return -1;
}

//=============================================================================
// Calls implementation-specific clearBuffer
//=============================================================================
void Socket::clearBuffer()
{
  if (socket_impl)
  {
    socket_impl->clearBuffer();
  }
}

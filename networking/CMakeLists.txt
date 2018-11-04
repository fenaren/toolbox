target_include_directories(toolbox PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/..)

#Include platform-independent sources
target_sources(toolbox PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/ArpPacket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ArpPacketBase.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ArpPacketEthernetIpv4.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Ipv4Address.cpp
  ${CMAKE_CURRENT_LIST_DIR}/MacAddress.cpp
  ${CMAKE_CURRENT_LIST_DIR}/NetworkAddress.cpp
  ${CMAKE_CURRENT_LIST_DIR}/RawSocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/RawSocketImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Socket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SocketFactory.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SocketImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/TCPSocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/TCPSocketImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/UDPSocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/UDPSocketImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/miscNetworking.cpp)

# Include platform-specific sources
if(WIN32)
  target_sources(toolbox PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/WindowsRawSocketImpl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WindowsSocketCommon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WindowsTCPSocketImpl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WindowsUDPSocketImpl.cpp)
else(WIN32)
  target_sources(toolbox PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/PosixSocketCommon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PosixTCPSocketImpl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PosixUDPSocketImpl.cpp)

  if(LINUX)
    target_sources(toolbox PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/LinuxRawSocketImpl.cpp)
  endif(LINUX)
endif(WIN32)

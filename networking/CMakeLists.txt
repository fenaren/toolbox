# Include common project setup
include(${PROJECT_SOURCE_DIR}/common/ProjectCommon.cmake)

# All the platform-independent source files in this directory
set(SRC
  ArpPacket.cpp
  ArpPacketBase.cpp
  ArpPacketEthernetIpv4.cpp
  EthernetIIHeader.cpp
  Ipv4Address.cpp
  MacAddress.cpp
  RawSocket.cpp
  RawSocketImpl.cpp
  Socket.cpp
  SocketFactory.cpp
  SocketImpl.cpp
  TCPSocket.cpp
  TCPSocketImpl.cpp
  UDPSocket.cpp
  UDPSocketImpl.cpp
  miscNetworking.cpp)

# All the platform-dependent source files in this directory
if(WIN32)
  list(APPEND SRC
    WindowsRawSocketImpl.cpp
    WindowsSocketCommon.cpp
    WindowsTCPSocketImpl.cpp
    WindowsUDPSocketImpl.cpp)
else(WIN32)
  list(APPEND SRC
    PosixSocketCommon.cpp
    PosixTCPSocketImpl.cpp
    PosixUDPSocketImpl.cpp)
  if(LINUX)
    list(APPEND SRC LinuxRawSocketImpl.cpp)
  endif(LINUX)
endif(WIN32)

# Add source files to the project sources
list_prepend_to_each(SRC networking/)
target_sources(${PROJECT_NAME} PRIVATE ${SRC})

# Add this directory to the project includes
target_include_directories(${PROJECT_NAME} PUBLIC .)

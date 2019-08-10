include(${PROJECT_SOURCE_DIR}/tools-cmake/ProjectCommon.cmake)

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
  UDPSocketImpl.cpp)

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
    PosixUDPSocketImpl.cpp
    miscNetworking.cpp)
  if(LINUX)
    list(APPEND SRC LinuxRawSocketImpl.cpp)
  endif(LINUX)
endif(WIN32)

# Add source files to the project sources
list_prepend_to_each(SRC networking/)
target_sources(${PROJECT_NAME} PRIVATE ${SRC})

# Add this directory to the project includes
target_include_directories(${PROJECT_NAME} PUBLIC .)

# Add test subdirectories (these don't build unconditionally)
add_subdirectory(ArpPacket_test             EXCLUDE_FROM_ALL)
add_subdirectory(ArpPacketEthernetIpv4_test EXCLUDE_FROM_ALL)
add_subdirectory(EthernetIIHeader_test      EXCLUDE_FROM_ALL)
add_subdirectory(Ipv4Address_test           EXCLUDE_FROM_ALL)
add_subdirectory(MacAddress_test            EXCLUDE_FROM_ALL)
add_subdirectory(RawSocket_test             EXCLUDE_FROM_ALL)
add_subdirectory(TCPSocket_test             EXCLUDE_FROM_ALL)
add_subdirectory(UDPSocket_test             EXCLUDE_FROM_ALL)
add_subdirectory(miscNetworking_test        EXCLUDE_FROM_ALL)

if(MACOS OR LINUX)
endif(MACOS OR LINUX)

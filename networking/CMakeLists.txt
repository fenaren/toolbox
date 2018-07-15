target_include_directories(toolbox PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/..)

#Include platform-independent sources
target_sources(toolbox PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Ipv4Address.cpp
  ${CMAKE_CURRENT_LIST_DIR}/MacAddress.cpp
  ${CMAKE_CURRENT_LIST_DIR}/NetworkAddress.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Socket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SocketFactory.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SocketImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/TCPSocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/TCPSocketImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/UDPSocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/UDPSocketImpl.cpp)

# Include platform-specific sources
if(LINUX)
  target_sources(toolbox PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/LinuxRawSocket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LinuxSocketCommon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LinuxTCPSocketImpl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LinuxUDPSocketImpl.cpp)
elseif(WIN32)
  target_sources(toolbox PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/WindowsRawSocket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WindowsSocketCommon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WindowsTCPSocketImpl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WindowsUDPSocketImpl.cpp)
endif(LINUX)

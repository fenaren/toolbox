target_include_directories(toolbox PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_sources(toolbox PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/LinuxRawSocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/LinuxSocketCommon.cpp
  ${CMAKE_CURRENT_LIST_DIR}/LinuxTCPSocketImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/LinuxUDPSocketImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/MacAddress.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Socket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SocketFactory.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SocketImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/TCPSocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/TCPSocketImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/UDPSocket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/UDPSocketImpl.cpp)

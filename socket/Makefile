# Socket library makefile
# Leigh Garbs

LIB_NAME := libsocket

OBJ := \
LinuxRawSocket.o \
LinuxSocketCommon.o \
LinuxTCPSocketImpl.o \
LinuxUDPSocketImpl.o \
Socket.o \
SocketFactory.o \
SocketImpl.o \
TCPSocket.o \
TCPSocketImpl.o \
UDPSocket.o \
UDPSocketImpl.o

# Implicit rule specifying how to make object files
%.o: %.cpp %.hpp
	$(CC) -DLINUX -fPIC -Wall -g2 -c -o $@ $<

all: $(LIB_NAME).a $(LIB_NAME).so

$(LIB_NAME).a: $(OBJ)
	ar rcs $@ $?

$(LIB_NAME).so: $(OBJ)
	gcc -shared -Wl,-soname,$(LIB_NAME).so -o $(LIB_NAME).so $(OBJ)

clean:
	rm $(LIB_NAME).a $(LIB_NAME).so $(OBJ)

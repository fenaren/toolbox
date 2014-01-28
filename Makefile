# Toolbox library makefile
# Leigh Garbs

# Name of libraries to be produced; appropriate .a or .so extension will be added later
LIB_NAME := libtoolbox

# Compilation is done with g++
CC := g++
CFLAGS := -DLINUX -fPIC -Wall -g2 -c

# List of directories containing source files
DIRECTORY_LIST := \
sockets \
logging \
netstructs

# Where the built object files go
OBJ_DIR := obj


SOCKETS_OBJ := \
LinuxRawSocket.o \
LinuxSocketCommon.o \
LinuxTCPSocketImpl.o \
LinuxUDPSocketImpl.o \
SocketFactory.o \
SocketImpl.o \
TCPSocket.o \
TCPSocketImpl.o \
UDPSocket.o \
UDPSocketImpl.o

LOGGING_OBJ := \
Log.o

# Netstructs is nothing but headers at the moment
NETSTRUCTS_OBJ :=

# The final list of all object files
OBJ := \
$(SOCKETS_OBJ) \
$(LOGGING_OBJ) \
$(NETSTRUCTS_OBJ)

OBJ_FULL_PATH := $(addprefix $(OBJ_DIR)/, $(OBJ))

# Set the search path
vpath %.cpp $(DIRECTORY_LIST)
vpath %.hpp $(DIRECTORY_LIST)


all: $(LIB_NAME).a $(LIB_NAME).so

$(LIB_NAME).a: $(OBJ_FULL_PATH)
	ar rcs $@ $?

$(LIB_NAME).so: $(OBJ_FULL_PATH)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^

# Implicit rule specifying how to make object files
$(OBJ_DIR)/%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-rm $(LIB_NAME).a $(LIB_NAME).so $(OBJ_FULL_PATH)

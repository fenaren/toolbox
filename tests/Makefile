# Toolbox tests makefile
# Leigh Garbs

# Compilation is done with g++
CC := g++
CFLAGS := -DLINUX -Wall -g2

TOOLBOX_INC := -I../misc -I../networking
TOOLBOX_A   := ../libtoolbox.a
TOOLBOX_SO  := ../libtoolbox.so

all: logtest macaddresstest

toolbox:
	make -C ..

logtest: toolbox logtest.cpp
	@$(CC) -o $@ $(TOOLBOX_INC) logtest.cpp $(TOOLBOX_A)

macaddresstest: toolbox macaddresstest.cpp
	@$(CC) -o $@ $(TOOLBOX_INC) macaddresstest.cpp $(TOOLBOX_A)

CXX=g++
VCPKG_ROOT=/home/ahmad/programs/vcpkg/installed/x64-linux-clang

# TODO: -O2 after debug
CXX_FLAGS=-O2 -c -m32 -std=c++23 -g
LINK_FLAGS=-O2 -no-pie -m32 -g

# CXXFLAGS=-I$(pwd)/installed/x64-linux/include
# CFLAGS=-I$(pwd)/installed/x64-linux/include
# LDFLAGS=-L$(pwd)/installed/x64-linux/lib
# PKG_CONFIG_PATH=$(pwd)/installed/x64-linux/lib/pkgconfig:$(pwd)/installed/x64-linux/share/pkgconfig:$PKG_CONFIG_PATH

test.o:
	$(CXX) $(CXX_FLAGS) test.cc -o test.o

01-arctan-sse-serial.o:
	nasm -g -f elf32 01-arctan-sse-serial.asm -o 01-arctan-sse-serial.o

02-arctan-sse-parallel.o:
	nasm -g -f elf32 02-arctan-sse-parallel.asm -o 02-arctan-sse-parallel.o

test-serial.out: 01-arctan-sse-serial.o test.o
	$(CXX) $(LINK_FLAGS) -o test-serial.out \
		01-arctan-sse-serial.o \
		test.o
	-rm *.o

test-parallel.out: 02-arctan-sse-parallel.o test.o
	$(CXX) $(LINK_FLAGS) -o test-parallel.out \
		02-arctan-sse-parallel.o \
		test.o
	-rm *.o


test-serial: clean test-serial.out
	./test-serial.out
	echo "Success!"

test-parallel: clean test-parallel.out
	./test-parallel.out
	echo "Success!"

clean:
	-rm *.out
	-rm *.o

.PHONY: clean

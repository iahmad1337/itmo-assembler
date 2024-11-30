CXX=clang++
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

01-max-signed.o:
	nasm -g -f elf32 01-max-signed.asm -o 01-max-signed.o

02-max-unsigned.o:
	nasm -g -f elf32 02-max-unsigned.asm -o 02-max-unsigned.o

test.out: 01-max-signed.o 02-max-unsigned.o test.o
	$(CXX) $(LINK_FLAGS) -o test.out \
		test.o \
		01-max-signed.o \
		02-max-unsigned.o
	-rm *.o


test: clean test.out
	./test.out
	echo "Success!"

clean:
	-rm *.out
	-rm *.o

.PHONY: clean

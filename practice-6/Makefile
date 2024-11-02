CXX=clang++
VCPKG_ROOT=/home/ahmad/programs/vcpkg/installed/x64-linux-clang

# TODO: -O2 after debug
CXX_FLAGS=-O2 -c -m32 -std=c++23 -g
LINK_FLAGS=-O2 -no-pie -m32 -g

# CXXFLAGS=-I$(pwd)/installed/x64-linux/include
# CFLAGS=-I$(pwd)/installed/x64-linux/include
# LDFLAGS=-L$(pwd)/installed/x64-linux/lib
# PKG_CONFIG_PATH=$(pwd)/installed/x64-linux/lib/pkgconfig:$(pwd)/installed/x64-linux/share/pkgconfig:$PKG_CONFIG_PATH

01-arctan-test.o:
	$(CXX) $(CXX_FLAGS) 01-arctan-test.cc -o 01-arctan-test.o

01-arctan.o:
	nasm -g -f elf32 01-arctan.asm -o 01-arctan.o

01-arctan-test.out: 01-arctan.o 01-arctan-test.o
	$(CXX) $(LINK_FLAGS) -o 01-arctan-test.out \
		01-arctan.o \
		01-arctan-test.o
	-rm *.o


test: clean 01-arctan-test.out
	./01-arctan-test.out
	echo "Success!"

clean:
	-rm *.out
	-rm *.o

.PHONY: clean

CXX=clang++
VCPKG_ROOT=/home/ahmad/programs/vcpkg/installed/x64-linux-clang

# TODO: -O2 after debug
CXX_FLAGS=-O2 -c -m32 -std=c++23 -g
LINK_FLAGS=-O2 -no-pie -m32 -g

# CXXFLAGS=-I$(pwd)/installed/x64-linux/include
# CFLAGS=-I$(pwd)/installed/x64-linux/include
# LDFLAGS=-L$(pwd)/installed/x64-linux/lib
# PKG_CONFIG_PATH=$(pwd)/installed/x64-linux/lib/pkgconfig:$(pwd)/installed/x64-linux/share/pkgconfig:$PKG_CONFIG_PATH

# gcc -no-pie -m32 -o $(1).out $(1).o

define test_template =
nasm -g -f elf32 $(1).asm -o $(1).o
$(CXX) $(CXX_FLAGS) $(2) -o $(2).o
$(CXX) $(LINK_FLAGS) -o $(1).out \
	$(1).o \
	$(2).o
-rm *.o
endef

01-1-byte-move-serial.out:
	$(call test_template,01-1-byte-move-serial,test-byte-move.cc)

01-2-byte-move-sse.out:
	$(call test_template,01-2-byte-move-sse,test-byte-move.cc)

test-byte-move: clean 01-1-byte-move-serial.out 01-2-byte-move-sse.out
	./01-1-byte-move-serial.out
	./01-2-byte-move-sse.out
	echo "Success!"

clean:
	-rm *.out
	-rm *.o

.PHONY: clean

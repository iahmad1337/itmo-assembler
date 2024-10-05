CXX=g++
CXX_FLAGS=-c -m32 -std=c++20 -fsanitize=undefined,address
CC=gcc
C_FLAGS=-c -m32 -std=c99 -fsanitize=undefined,address
LINK_FLAGS=-no-pie -m32 -fsanitize=undefined,address

define target_template =
nasm -g -f elf32 $(1).asm -o $(1).o
gcc -no-pie -m32 -o $(1).out $(1).o
rm $(1).o
endef

nth-prime-cpp.o:
	$(CXX) $(CXX_FLAGS) nth-prime.cc -o nth-prime-cpp.o

nth-prime-c.o:
	$(CC) $(C_FLAGS) nth-prime.c -o nth-prime-c.o

01-c-from-asm.out: nth-prime-c.o
	nasm -g -f elf32 01-c-from-asm.asm -o 01-c-from-asm.o
	$(CC) $(LINK_FLAGS) -o 01-c-from-asm.out \
		01-c-from-asm.o \
		nth-prime-c.o
	-rm *.o


test: 01-c-from-asm.out
	./01-c-from-asm.out
	echo "Success!"

clean:
	-rm *.out
	-rm *.o

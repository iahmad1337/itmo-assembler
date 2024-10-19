CXX=g++
CXX_FLAGS=-O2 -c -m32 -std=c++20 -fsanitize=undefined,address
CC=gcc
C_FLAGS=-O2 -c -m32 -std=c99 -fsanitize=undefined,address
LINK_FLAGS=-O2 -no-pie -m32 -fsanitize=undefined,address

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

02-cpp-from-asm.out: nth-prime-cpp.o
	nasm -g -f elf32 02-cpp-from-asm.asm -o 02-cpp-from-asm.o
	$(CC) $(LINK_FLAGS) -o 02-cpp-from-asm.out \
		02-cpp-from-asm.o \
		nth-prime-cpp.o
	-rm *.o


test: clean 01-c-from-asm.out 02-cpp-from-asm.out
	./01-c-from-asm.out
	./02-cpp-from-asm.out
	echo "Success!"

clean:
	-rm *.out
	-rm *.o

.PHONY: clean

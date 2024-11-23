CXX=clang++

LINK_FLAGS=-O2 -no-pie -g -lc

01-hello-x64.o:
	nasm -g -f elf64 01-hello-x64.asm -o 01-hello-x64.o

01-hello-x64.out: 01-hello-x64.o
	$(CXX) $(LINK_FLAGS) -o 01-hello-x64.out 01-hello-x64.o
	-rm *.o


test: clean 01-hello-x64.out
	./01-hello-x64.out
	echo "Success!"

clean:
	-rm *.out
	-rm *.o

.PHONY: clean

all: elf32 elf64

elf32:
	nasm -g -f elfx32 hello-world.asm -o hw-elf32.o
	gcc -march=elf32-x86-64 -o hw-elf32.out hw-elf32.o

elf64:
	nasm -g -f elf64 hello-world.asm -o hw-elf64.o
	gcc -march=elf64-x86-64 -o hw-elf64.out hw-elf64.o

clean:
	rm *.o *.out

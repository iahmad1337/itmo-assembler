elf32:
	nasm -g -f elf32 hello-world.asm -o elf32.o
	gcc -m32 -o elf32.out elf32.o
	rm elf32.o

test: elf32
	./elf32.out && echo "Success" || echo "Fail"

clean:
	rm *.out

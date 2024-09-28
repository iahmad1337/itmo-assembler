elf32:
	nasm -g -f elf32 hello-world.asm -o hello-world.o
	gcc -no-pie -m32 -o hello-world.out hello-world.o
	rm hello-world.o

04:
	nasm -g -f elf32 04-factorial.asm -o 04.o
	gcc -no-pie -m32 -o 04.out 04.o
	rm 04.o

test: elf32 04
	./hello-world.out && echo "Success" || echo "****FAIL****"
	./04.out && echo "Success" || echo "****FAIL****"

clean:
	rm *.out

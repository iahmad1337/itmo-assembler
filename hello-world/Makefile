hello-world.out:
	nasm -g -f elf32 hello-world.asm -o hello-world.o
	gcc -no-pie -m32 -o hello-world.out hello-world.o
	rm hello-world.o

04.out:
	nasm -g -f elf32 04-factorial.asm -o 04.o
	gcc -no-pie -m32 -o 04.out 04.o
	rm 04.o

05.out:
	nasm -g -f elf32 05-factorial.asm -o 05.o
	gcc -no-pie -m32 -o 05.out 05.o
	rm 05.o

test: hello-world.out 04.out 05.out
	./hello-world.out && echo "Success" || echo "****FAIL****"
	./04.out && echo "Success" || echo "****FAIL****"
	./05.out && echo "Success" || echo "****FAIL****"

clean:
	rm *.out

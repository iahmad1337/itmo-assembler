define target_template =
nasm -g -f elf32 $(1).asm -o $(1).o
gcc -no-pie -m32 -o $(1).out $(1).o
rm $(1).o
endef

03-factorial.out:
	$(call target_template,03-factorial)

04-factorial.out:
	$(call target_template,04-factorial)

05-factorial.out:
	$(call target_template,05-factorial)

test: 03-factorial.out 04-factorial.out 05-factorial.out
	./03-factorial.out
	./04-factorial.out
	./05-factorial.out
	echo "Success!"

clean:
	rm *.out

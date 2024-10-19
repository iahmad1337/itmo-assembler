Тут важно попробовать все состыковки, даже если придется замангленное имя звать! Ну и разные конвенции вызовов.
В идеальном мире лучше лучше всегда использовать только сишный интерфейс!!!

0) Write a "n-th prime" function in C++ and C
1) Call the C function from assembler and print the value
2) Call the C++ function from assembler and print the value
3) Call a C++ method
4) Call a C++ virtual method
5) Call an asm function from C
6) Call an asm function from C++
7*) Call a C function, that returns a large struct by value
8*) Call a C++ function, that returns a large struct by value

Note: don't touch return addresses, because "shadow stack" will terminate your
program because of supposed security threats.
Also, speed may be affected if you touch return addresses, as branch predictor
relies heavily on the stack contents.

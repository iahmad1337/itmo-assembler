1. Make an executable that does nothing, in elf32
2. Write a hello world using printf
3. Print factorial of a fixed number
4. Print factorial, but render the printed number manually
    - mutable registers:
        - eax
        - ecx
        - edx
        - esp
    - "immutable" registers:
        - ebx
        - ebp
        - esi
        - edi
    - mul:
        - acc == edx:eax
        - acc == arg * eax
    - div:
        - divisor = arg
        - dividend = edx:eax
        - Result: quotient = eax, residual = edx
5. Print factorial, render the printed number manually and the buffer must be on
   the stack


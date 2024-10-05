global main
extern printf
extern NthPrime

section .text

main:
    push ebx
    push edi  ; save, because we will modify it.
              ; Can't use e.g. ecx, because the called functions may modify it

    push dword program_description
    call printf
    add esp, 4

    mov edi, 1  ; loop variable: 1...total_inputs
print_loop:
    mov ebx, [nth_prime_inputs+edi*4-4]  ; n
    push ebx
    call NthPrime
    add esp, 4

    push eax
    push ebx
    push dword format
    call printf
    add esp, 12

    add edi, 1
    test edi, total_inputs
    jne print_loop

    pop edi
    pop ebx

    xor eax, eax
    ret

section .rodata
program_description:
    db "Calling C version from asm:", 0Ah, 0
format:
    db "NthPrime(%d)=%d", 0Ah, 0
nth_prime_inputs:
    dd -1, 0, 1, 2, 3, 10, 1000

total_inputs equ ($-nth_prime_inputs)/4


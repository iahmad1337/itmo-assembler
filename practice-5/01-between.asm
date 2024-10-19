global main
extern printf

section .text

x:
    ret

main:
    push ebx
    push edi  ; save, because we will modify it.
              ; Can't use e.g. ecx, because the called functions may modify it

    mov al, '9'
    cmp al, '0'
    jb invalid
    cmp al, '9'
    ja invalid
    jmp valid

invalid:
    ret

valid:
    ret

while:
    cmp eax, ecx
    jae past_while
    ; ...
    jmp while
past_while:
    ; past while
print_loop:
    mov ebx, [inputs+edi-1]  ; n

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
    db "Determining, whether :", 0Ah, 0
format_is_digit:
    db "%c is digit", 0Ah, 0
format_is_not_digit:
    db "%c is not a digit", 0Ah, 0
inputs:
    db -1, 0, 1, 2, 3, 10, 1000, 'a', '9'

total_inputs equ ($-inputs)


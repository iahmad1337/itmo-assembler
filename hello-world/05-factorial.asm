global main
extern printf

section .text

render:
    ; arg1 - number to render
    ; arg2 - address to store the rendered number
    mov ecx, [esp + 8]  ; address to store the rendered number
    mov eax, [esp + 4]  ; number to render
    ; NOTE: call address is on the bottom of the stack, so we have to erase 4
    ; more bytes!!!

    push ebx
    mov ebx, 10  ; divisor
    push esi
    mov esi, ecx  ; start of the buffer

.render_loop:
    xor edx, edx
    div ebx
    ; digit is now in edx
    add edx, '0'
    mov [ecx], edx
    add ecx, 1
    test eax, eax
    jnz .render_loop

    mov byte [ecx], 0  ; null-terminator
    sub ecx, 1  ; ecx points last digit, esi - to the first

.reverse_digits_loop:
    mov bl, [ecx]
    mov al, [esi]
    mov [ecx], al
    mov [esi], bl
    sub ecx, 1
    add esi, 1
    test esi, ecx
    jb .reverse_digits_loop

    pop esi
    pop ebx

    ret

main:
    mov ecx, [factorial_input]
    mov eax, 1
factorial_loop_start:
    mul ecx
    sub ecx, 1
    jnz factorial_loop_start

    sub esp, [buffer_size]
    mov ecx, esp

    push ecx
    push eax
    call render
    pop eax
    pop ecx

    push ecx
    push format
    call printf
    add esp, 8

    add esp, [buffer_size]

    xor eax, eax
    ret

; may also be .rdata (or .data for mutable data)
section .rodata
format:
    db "Factorial rendered on stack is %s", 0Ah, 0
factorial_input:
    dd 0Ah ; value of which to calculate factorial
buffer_size:
    dd 100h ; 256 bytes for buffer

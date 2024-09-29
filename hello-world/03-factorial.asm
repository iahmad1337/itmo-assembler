global main
extern printf

section .text

main:
    mov ecx, 5
    mov eax, 1
loop_start:
    mul ecx
    sub ecx, 1
    jnz loop_start

    push eax
    push format
    call printf
    add esp, 8

    xor eax, eax
    ret

; may also be .rdata (or .data for mutable data)
section .rodata
format:
    db "Hello, world! Factorial 5 is %d", 0Ah, 0
; db - for bytes, dw - words, dd - double words
; in nasm the convention is `0Ah` instead of `0xA`

global main
extern printf

section .text

main:
    mov eax, 42
    push eax
    push format
    call printf
    add esp, 8

    xor eax, eax
    ret

; may also be .rdata (or .data for mutable data)
section .rodata
format:
    db "Hello, world! The number is %d", 0Ah, 0
; db - for bytes, dw - words, dd - double words

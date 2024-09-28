global main
extern printf

section .text

main:
    push dword 42
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

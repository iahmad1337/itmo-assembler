global main
extern printf

section .text

main:
    push format
    call printf
    add esp, 4

    xor eax, eax
    ret

; may also be .rdata (or .data for mutable data)
section .rodata
format:
    db "Hello, world!", 0Ah, 0
; db - for bytes, dw - words, dd - double words
; in nasm the convention is `0Ah` instead of `0xA`

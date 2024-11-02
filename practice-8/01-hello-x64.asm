global main
extern printf

section .text

main:
    sub rsp, 8  ; Stack alignment

    ; Stack is now aligned by 16 bytes

    lea rdi, [format]
    call printf

    xor eax, eax
    xor rdx, rdx
    add rsp, 8 ; Stack alignment
    ret

; may also be .rdata (or .data for mutable data)
section .rodata
format:
    db "Hello, world!", 0Ah, 0
; db - for bytes, dw - words, dd - double words
; in nasm the convention is `0Ah` instead of `0xA`

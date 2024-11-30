global MyArctan

section .text


MyArctan:
    ; A cdecl funnction: MyArctan(float x, ui32 n) -> float
    ; fld dword [esp + 4]  ; st0 = x
    mov eax, [esp + 8]  ; eax = n

    movss xmm0, [esp + 4]  ; numerator

    movss xmm1, [one]  ; denominator

    movss xmm2, xmm0  ; multiplier
    mulss xmm2, xmm2
    mulss xmm2, [minus_one]

    movss xmm4, [zero]  ; accumulator

    cmp eax, 0
    jz arctan_return
arctan_loop:
    movss xmm5, xmm0
    divss xmm5, xmm1

    addss xmm4, xmm5

    mulss xmm0, xmm2
    addss xmm1, [two]

    sub eax, 1
    jnz arctan_loop

arctan_return:
    sub esp, 4
    movss [esp], xmm4
    emms
    fld dword [esp]  ; put the return value back in st0
    add esp, 4

    ret


; may also be .rdata (or .data for mutable data)
section .rodata
zero:
    dd 0.0
one:
    dd 1.0
minus_one:
    dd -1.0
two:
    dd 2.0

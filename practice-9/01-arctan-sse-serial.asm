global MyArctan

section .text


MyArctan:
    ; A cdecl funnction: MyArctan(float x, ui32 n) -> float
    ; fld dword [esp + 4]  ; st0 = x
    mov eax, [esp + 8]  ; eax = n

    movss xmm0, dword [esp + 4]  ; numerator

    cvtpi2ps xmm1, [one]  ; denominator

    movss xmm2, xmm0  ; multiplier
    mulss xmm2, xmm2
    cvtpi2ps xmm3, [minus_one]
    mulss xmm2, xmm3


    cvtpi2ps xmm3, [two]  ; summand for denominator


    cvtpi2ps xmm4, [zero]  ; accumulator

    cmp eax, 0
    jz arctan_return
arctan_loop:
    ; Starting loop with
    ; st4(numerator), st3(2), st2(-x*x), st1(denominator), st0(accumulator)
    movss xmm5, xmm0
    divss xmm5, xmm1

    addss xmm4, xmm5

    mulss xmm0, xmm2
    addss xmm1, xmm3

    sub eax, 1
    jnz arctan_loop

; Invariant: the result is in xmm0
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
    dd 00h
one:
    dd 01h
minus_one:
    dd 0FFFFFFFFh
two:
    dd 02h ; value of which to calculate factorial

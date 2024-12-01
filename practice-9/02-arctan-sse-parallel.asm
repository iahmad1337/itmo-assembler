global MyArctan

section .text


MyArctan:
    ; A cdecl funnction: MyArctan(float x, ui32 n) -> float
    ; [esp + 4] = x
    ; [esp + 8] = n

    mov eax, [esp + 8]  ; n

    ; xmm[0..3] are reserved, any other registers may be used for interim
    ; calculations

    ; Can't just do `movss xmm5, [...]` because this form zero-extends all higher
    ; 96 bits. So instead we do `movss xmm*, xmm4`
    movss xmm4, [one]

    ;;;;;;;;;;;;;;;;;;;;;;
    ;  Numerator (xmm0)  ;
    ;;;;;;;;;;;;;;;;;;;;;;
    movss xmm0, [esp + 4]
    movss xmm5, [esp + 4]
    mulss xmm5, xmm5
    pshufd xmm5, xmm5, 00000000b  ; [0 0 0 x^2] -> [x^2 x^2 x^2 x^2]
    movss xmm5, xmm4  ; [x^2 x^2 x^2 x^2] -> [x^2 x^2 x^2 1]

    pshufd xmm0, xmm0, 00000000b  ; [0 0 0 x] -> [x x x x]
    mulps xmm0, xmm5  ; [x x x x] -> [x^3 x^3 x^3 x]

    pshufd xmm5, xmm5, 11110000b  ; [x^2 x^2 x^2 1] -> [x^2 x^2 1 1]
    mulps xmm0, xmm5  ; [x^3 x^3 x^3 x] -> [x^5 x^5 x^3 x]

    pshufd xmm5, xmm5, 11000000b  ; [x^2 x^2 1 1] -> [x^2 1 1 1]
    mulps xmm0, xmm5  ; [x^5 x^5 x^3 x] -> [x^7 x^5 x^3 x]

    mulps xmm0, [plus_minus_ones]  ; [-x^7 x^5 -x^3 x]

    ;;;;;;;;;;;;;;;;;;;;;;;;
    ;  Denominator (xmm1)  ;
    ;;;;;;;;;;;;;;;;;;;;;;;;
    movaps xmm1, [denominator_init]  ; denominator (notice the alignment on mov)

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;  Numerator multiplier (xmm2)  ;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    movss xmm2, [esp + 4]  ; [0 0 0 x]
    mulss xmm2, xmm2  ; x -> x^2
    mulss xmm2, xmm2  ; x^2 -> x^4
    mulss xmm2, xmm2  ; x^4 -> x^8
    pshufd xmm2, xmm2, 00000000b  ; [0, 0, 0, x^8] -> [x^8, x^8, x^8, x^8]

    ;;;;;;;;;;;;;;;;;;;;;;;;
    ;  Accumulator (xmm3)  ;
    ;;;;;;;;;;;;;;;;;;;;;;;;
    movaps xmm3, [zeroes]  ; [s3 s2 s1 s0] = [0 0 0 0]

    cmp eax, 0
    jz arctan_return
arctan_loop:
    movaps xmm4, xmm0
    divps xmm4, xmm1

    addps xmm3, xmm4

    mulps xmm0, xmm2
    addps xmm1, [denominator_summand]

    ; TODO: test with n not divisible by 4
    sub eax, 4
    jnz arctan_loop

arctan_return:
    movaps xmm4, [zeroes]

    pshufd xmm4, xmm3, 00001110b

    addps xmm4, xmm3  ; [_ _ s3 s2] -> [__ __ (s3+s1) (s2+s0)]

    pshufd xmm3, xmm4,  00000001b  ; [s3, s2, s1, s0] -> [_, _, _, (s3+s1)]

    addps xmm4, xmm3  ; [_ _ _ (s2+s0)] -> [_ _ _ (s2+s0+s3+s1)]

    sub esp, 4
    movss [esp], xmm4
    emms
    fld dword [esp]  ; put the return value back in st0
    add esp, 4

    ret


; may also be .rdata (or .data for mutable data)
section .rodata
one:
    dd 1.0

align 16
zeroes:
    dd 0.0, 0.0, 0.0, 0.0
ones:
    dd 1.0, 1.0, 1.0, 1.0
plus_minus_ones:
    dd 1.0, -1.0, 1.0, -1.0
denominator_init:
    dd 1.0, 3.0, 5.0, 7.0
denominator_summand:
    dd 8.0, 8.0, 8.0, 8.0

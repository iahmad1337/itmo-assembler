global MyArctan

section .text


MyArctan:
    ; A cdecl funnction: MyArctan(float x, ui32 n) -> float
    fld dword [esp + 4]  ; st0 = x
    mov eax, [esp + 8]  ; eax = n

    fld st0  ; st1, st0 = x, x
    fmul st0, st1  ; st1, st0 = x, x*x
    fldz  ; st2, st1, st0 = x, x*x, 0
    fsub st0, st1  ; st2(numerator), st1, st0 = x, x*x, -x*x
    fld1  ; st3(numerator), st2, st1, st0(denominator) = x, x*x, -x*x, 1
    fldz  ; st4(numerator), st3, st2, st1(denominator), st0(accumulator) = x, x*x, -x*x, 1, 0
    fld1  ; st5(numerator), st4, st3, st2(denominator), st1(accumulator), st0 = x, x*x, -x*x, 1, 0, 1
    fadd st0, st0  ; st5(numerator), st4, st3, st2(denominator), st1(accumulator), st0 = x, x*x, -x*x, 1, 0, 2
    fxch st4  ; st5(numerator), st4, st3, st2(denominator), st1(accumulator), st0 = x, 2, -x*x, 1, 0, 2
    fstp st0  ; st4(numerator), st3, st2, st1(denominator), st0(accumulator)= x, 2, -x*x, 1, 0



    cmp eax, 0
    jz arctan_return
arctan_loop:
    ; Starting loop with
    ; st4(numerator), st3(2), st2(-x*x), st1(denominator), st0(accumulator)

    ; Add current summand to current sum
    fld st4       ; st5(num), st4, st3, st2(denom), st1(ac), st0 = num, 2, -x*x, denom, ac, numerator
    fdiv st0, st2  ; st5(num), st4, st3, st2(denom), st1(ac), st0 = num, 2, -x*x, denom, ac, num / denom
    faddp        ; st4(num), st3, st2, st1(denom), st0(new-ac) = num, 2, -x*x, denom, ac + num / denom

    ; Now do: numerator' = prev * -x*x, denominator' = denominator + 2

    ; renew numerator
    fld st4  ; st5(num), st4, st3, st2(denom), st1(new-ac), st0(num) = new-num, 2, -x*x, denom, new-ac, num
    fmul st0, st3  ; st5(num), st4, st3, st2(denom), st1(new-ac), st0(new-num) = new-num, 2, -x*x, denom, new-ac, num * (-x*x)
    fxch  st5  ; st5(new-num), st4, st3, st2(denom), st1(new-ac), st0(new-num) = new-num, 2, -x*x, denom, new-ac, new-num
    fstp st0  ; st4(new-num), st3, st2, st1(denom), st0(new-ac) = new-num, 2, -x*x, denom, new-ac

    ; renew denominator
    fld st1  ; st5(new-num), st4, st3, st2(denom), st1(new-ac), st0(denom) = new-num, 2, -x*x, denom, new-ac, denom
    fadd st0, st4  ; st5(new-num), st4, st3, st2(denom), st1(new-ac), st0(new-denom) = new-num, 2, -x*x, denom, new-ac, denom+2
    fxch st2  ; st5(new-num), st4, st3, st2(new-denom), st1(new-ac), st0(new-denom) = new-num, 2, -x*x, new-denom, new-ac, denom+2
    fstp st0  ; st4(new-num), st3, st2, st1(new-denom), st0(new-ac) = new-num, 2, -x*x, new-denom, new-ac

    sub eax, 1
    jnz arctan_loop

arctan_return:

    sub esp, 4
    fst dword [esp]

    fstp st4
    fstp st3
    fstp st2
    fstp st1
    fstp st0

    fld dword [esp]  ; put the return value back in st0
    add esp, 4

    ret

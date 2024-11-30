global MaxElementSigned

section .text


MaxElementSigned:
    ; A cdecl funnction: MaxElementSigned(i8* dst, const i8* src, ui32 n) -> void
    mov eax, [esp + 4]  ; start of dst array
    mov ecx, [esp + 8]  ; start of src array
    mov edx, [esp + 12]  ; n

    cmp edx, 0
    jz MaxElementSigned_ret

MaxElementSigned_loop:
    movq mm0, [eax]
    movq mm1, [ecx]

    movq mm2, mm0
    movq mm3, mm1

    pcmpgtb mm2, mm1  ; mm2 is ones if mm0 is max
    pxor mm3, mm3
    pandn mm3, mm0  ; mm3 is ones if mm1 is max

    ; now calculate result (in mm0)
    pand mm0, mm2
    pand mm1, mm3
    por mm0, mm1

    movq [eax], mm0
    add eax, 4
    add ecx, 4

    sub edx, 4
    jnz MaxElementSigned_loop

MaxElementSigned_ret:
    ret

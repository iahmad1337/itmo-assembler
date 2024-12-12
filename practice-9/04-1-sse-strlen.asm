global MyStrlen

section .text


MyStrlen:
    ; A cdecl funnction: MyArctan(const char* c_str) -> float
    ; [esp + 4] = c_str

    mov eax, [esp + 4]  ; c_str - pointer to beginning of string
    mov ecx, eax  ; true start
    add eax, 0x0000000F
    and eax, 0xFFFFFFF0  ; round up eax to multiple of 16

    push ebx
    xor ebx, ebx  ; char count
    xor edx, edx  ; current char

    cmp ecx, eax
    je aligned_loop_prologue
beginning_loop:
    mov dl, byte[ecx]
    cmp dl, 0
    je strlen_end

    add ecx, 1
    add ebx, 1  ; increase string size
    cmp ecx, eax
    je aligned_loop_prologue
    jmp beginning_loop

; Main stage: aligned load and compare
aligned_loop_prologue:
    mov ecx, eax
    pxor xmm1, xmm1
aligned_loop:
    movaps xmm0, [eax]
    pcmpeqb xmm0, xmm1
    pmovmskb edx, xmm0  ; if the i-th bit in edx is 1, then we've got a 0-byte

    or edx, 0x10000
    bsf edx, edx

    cmp edx, 16
    jb aligned_loop_epilogue

    lea eax, [eax + 16]  ; may be faster than `add eax, 16`
    jmp aligned_loop

aligned_loop_epilogue:
    sub eax, ecx

    add ebx, edx
    add ebx, eax

strlen_end:
    mov eax, ebx

    pop ebx

    ret

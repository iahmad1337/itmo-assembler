global MyStrlen

section .text


MyStrlen:
    ; A cdecl funnction: MyArctan(const char* c_str) -> float
    ; [esp + 4] = c_str

    mov eax, [esp + 4]  ; c_str - pointer to beginning of string
    mov ecx, eax  ; true start
    add eax, 15
    and eax, 0xFFFFFFF0  ; round up eax to multiple of 16

    push ebx
    xor ebx, ebx  ; char count
    xor edx, edx  ; current char
beginning_loop:
    mov dl, byte[ecx]
    add ecx, 1
    add ebx, 1  ; increase string size
    cmp ecx, eax
    je beginning_loop_end
    cmp dl, 0
    jne beginning_loop
    ; we actually reached zero here
    sub ebx, 1  ; remove one extra zero-th byte
    jmp strlen_end

beginning_loop_end:

; Main stage: aligned load and compare
    pxor xmm1, xmm1
aligned_loop:
    movaps xmm0, [eax]
    pcmpeqb xmm1, xmm0
    pmovmskb edx, xmm1

    popcnt edx, edx
    add ebx, edx

    cmp edx, 16
    jb strlen_end

    add eax, 16
    ; lea eax, [eax + 16]  ; may be faster than `add`
    jmp aligned_loop

strlen_end:
    ; popcnt edx, edx
    ; add ebx, edx

    mov eax, ebx

    pop ebx

    ret

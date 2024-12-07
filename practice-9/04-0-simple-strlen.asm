global MyStrlen

section .text


MyStrlen:
    ; A cdecl funnction: MyArctan(const char* c_str) -> float
    ; [esp + 4] = c_str

    mov eax, [esp + 4]  ; c_str - pointer to beginning of string
    mov ecx, eax  ; n - char count

    xor edx, edx
strlen_loop:
    mov dl, byte[eax]
    add eax, 1
    cmp dl, 0
    jne strlen_loop

strlen_loop_end:
    sub eax, ecx
    sub eax, 1
    ret

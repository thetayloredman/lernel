bits 32

struc cpu_registers_t
    .eax: resd 1
    .ebx: resd 1
    .ecx: resd 1
    .edx: resd 1
    .esi: resd 1
    .edi: resd 1
    .ebp: resd 1
    .esp: resd 1
    .eip: resd 1
    .cs: resw 1
    .ds: resw 1
    .es: resw 1
    .fs: resw 1
    .gs: resw 1
    .ss: resw 1
    .eflags: resd 1
endstruc ; total size: 52 bytes

section .text
    global init_regs

; Small ASM stub to fill out the cpu_registers_t struct
; with the current CPU registers.
init_regs:
    push eax
    ; stack state (higher is top)
    ; -> eax at [esp]
    ; -> return address at [esp + 4]
    ; -> cpu_registers_t * (first parameter) at [esp + 8]
    ; move the pointer passed as the first parameter into eax
    mov eax, [esp + 8]
    mov [eax + cpu_registers_t.ebx], ebx
    mov [eax + cpu_registers_t.ecx], ecx
    mov [eax + cpu_registers_t.edx], edx
    mov [eax + cpu_registers_t.esi], esi
    mov [eax + cpu_registers_t.edi], edi
    mov [eax + cpu_registers_t.ebp], ebp
    mov [eax + cpu_registers_t.esp], esp
    mov [eax + cpu_registers_t.cs], cs
    mov [eax + cpu_registers_t.ds], ds
    mov [eax + cpu_registers_t.es], es
    mov [eax + cpu_registers_t.fs], fs
    mov [eax + cpu_registers_t.gs], gs
    mov [eax + cpu_registers_t.ss], ss
    ; now we want to get eflags, so we push it onto the stack and
    ; pop into ebx
    pushfd
    pop ebx
    mov [eax + cpu_registers_t.eflags], ebx
    ; now we'll move the return address into ebx
    mov ebx, [esp + 4]
    mov [eax + cpu_registers_t.eip], ebx
    ; now we need to save the original value of eax, using the value on the stack again at [esp]
    mov ebx, [esp]
    mov [eax + cpu_registers_t.eax], ebx
    ; restore ebx
    mov ebx, [eax + cpu_registers_t.ebx]
    ; and now we restore eax to it's original value.
    pop eax
    
    ret
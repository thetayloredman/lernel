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
endstruc

section .data
    global init_regs

; Small ASM stub to fill out the cpu_registers_t struct
; with the current CPU registers.
init_regs:
    mov [esp + 4 + cpu_registers_t.eax], eax
    mov [esp + 4 + cpu_registers_t.ebx], ebx
    mov [esp + 4 + cpu_registers_t.ecx], ecx
    mov [esp + 4 + cpu_registers_t.edx], edx
    mov [esp + 4 + cpu_registers_t.esi], esi
    mov [esp + 4 + cpu_registers_t.edi], edi
    mov [esp + 4 + cpu_registers_t.ebp], ebp
    mov [esp + 4 + cpu_registers_t.esp], esp
    mov [esp + 4 + cpu_registers_t.cs], cs
    mov [esp + 4 + cpu_registers_t.ds], ds
    mov [esp + 4 + cpu_registers_t.es], es
    mov [esp + 4 + cpu_registers_t.fs], fs
    mov [esp + 4 + cpu_registers_t.gs], gs
    mov [esp + 4 + cpu_registers_t.ss], ss
    push eax                                    ; save eax for later
    pushfd                                      ; push eflags onto the stack...
    pop eax                                     ; ...and pop into eax. these two would usually be something like "mov eax, eflags"...
                                                ; ...but you can't do that.
    mov [esp + 4 + cpu_registers_t.eflags], eax ; then we store eflags in the struct
    mov eax, [esp + 4]                          ; now we want to work with eip. this gets our return address into eax...
    mov [esp + 4 + cpu_registers_t.eip], eax    ; ...and stores it in the struct. sadly there is no "mov [ADDR1], [ADDR2]" so we use eax for this.
    pop eax                                     ; restore eax
    ret
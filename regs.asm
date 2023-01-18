; FIXME: why won't the debug symbols load here?
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
    mov [esp + 4 + 52 - cpu_registers_t.eax], eax
    mov [esp + 4 + 52 - cpu_registers_t.ebx], ebx
    mov [esp + 4 + 52 - cpu_registers_t.ecx], ecx
    mov [esp + 4 + 52 - cpu_registers_t.edx], edx
    mov [esp + 4 + 52 - cpu_registers_t.esi], esi
    mov [esp + 4 + 52 - cpu_registers_t.edi], edi
    mov [esp + 4 + 52 - cpu_registers_t.ebp], ebp
    mov [esp + 4 + 52 - cpu_registers_t.esp], esp
    mov [esp + 4 + 52 - cpu_registers_t.cs], cs
    mov [esp + 4 + 52 - cpu_registers_t.ds], ds
    mov [esp + 4 + 52 - cpu_registers_t.es], es
    mov [esp + 4 + 52 - cpu_registers_t.fs], fs
    mov [esp + 4 + 52 - cpu_registers_t.gs], gs
    mov [esp + 4 + 52 - cpu_registers_t.ss], ss
    ; pushfd pushes the EFLAGS register onto the stack
    ; the series of these two following operations was basically what "mov [...], eflags" should have been,
    ; but for some reason that isn't possible
    pushfd
    ; pop into eax -- we restore eax later
    pop eax
    ; do the actual move
    mov [esp + 4 + 52 - cpu_registers_t.eflags], eax
    ; now we're going to work on eip, so we read the stack pointer's value (points to return address)
    mov eax, [esp]
    mov [esp + 4 + 52 - cpu_registers_t.eip], eax
    mov eax, [esp + 4 + 52 - cpu_registers_t.eax]
    ret
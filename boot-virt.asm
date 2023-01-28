bits 32

; boot.asm calls here once the virtual memory is set up
section .text
    section .text
    global _virt_start
    extern main
    extern puts

_virt_start:
    xor  ebp, ebp ; so that the stack walker stops here
    mov  esp, virt_esp

    push ebx
    push eax
    ; main.c: void main(uint32_t, multiboot_info_t *)
    call main

    push exit_msg
    call puts
halt: ; loop in case of a NMI
    cli
    hlt
    jmp halt
    ret ;never

section .bss
    resb 8192
virt_esp:

section .data
exit_msg:
    db "boot: halting CPU", 0
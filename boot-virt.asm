bits 32

; boot.asm calls here once the virtual memory is set up
section .text
    section .text
    global _virt_start
    global boot_eax
    global boot_ebx
    extern main
    extern puts
    extern early_page_directory
    extern flush_tlb

_virt_start:
    xor  ebp, ebp ; the stack walking method uses a null ebp to find where to stop
    mov  esp, virt_esp

    mov [boot_eax], eax
    mov [boot_ebx], ebx

    ; Invalidate the initial mapping. Simply just zero out the first entry in the page directory
    mov dword [early_page_directory], 0
    call flush_tlb

    call main

    push exit_msg
    call puts
halt: ; loop in case of a NMI
    cli
    hlt
    jmp halt

section .bss
    resb 8192
virt_esp:
boot_eax: resd 1
boot_ebx: resd 1

section .data
exit_msg:
    db "boot: halting CPU", 0
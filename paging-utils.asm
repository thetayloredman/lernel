bits 32

section .text
    global reload_cr3

reload_cr3:
    mov eax, cr3
    mov cr3, eax
    ret


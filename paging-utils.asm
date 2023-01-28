bits 32

section .text
    global flush_tlb

flush_tlb:
    ; TODO: is there a faster way to do this?
    mov eax, cr3
    mov cr3, eax
    ret


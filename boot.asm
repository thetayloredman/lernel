bits 32

section .multiboot
    dd 0x1BADB002           ; magic number
    dd 0x0                  ; flags
    dd - (0x1BADB002 + 0x0) ; checksum

section .phys.text exec
    global _start
    extern _virt_start
    extern early_paging_init
    extern _physical_start
    extern _physical_end
_start:
    cli                     ; bye bye interrupts
    xor  ebp, ebp
    mov  esp, early_esp     ; set the stack pointer

    ; IMMEDIATELY after the stack is initialized,
    ; we push the eax and ebx registers onto the stack.
    ; if we do ANYTHING before this, the registers
    ; might be clobbered and we will lose access to our
    ; multiboot info structure!
    push ebx
    push eax

    ; ===== PAGING SETUP =====

    ; first, let's check that the kernel can fit in one page table
    ; if it can't, we'll have to do some more work in the future
    ; to have another table here
    mov eax, _physical_end
    sub eax, _physical_start
    cmp eax, 0x1000 * (1024-256)
    jae kernel_oversized
    jmp kernel_fits
kernel_oversized:
    mov esi, oversized
    mov edi, 0xb8000 ; VRAM
cpy_loop: ; memcpy() basically
    mov al, [esi]
    cmp al, 0
    je halt_loop
    mov [edi], al
    inc esi
    inc edi
    jmp cpy_loop
halt_loop:
    cli
    hlt
    jmp halt_loop
kernel_fits:
    ; woohoo! the kernel fits within the space we have!

    ; first, let's identity page VRAM
    ; VGA memory sita at 0xb8000
    ; in binary: 0000000000 0010111000 000000000000
    ;            pdir ent   ptab ent   offset
    ; this is pdir entry 0, ptab entry 184
    ; first, let's set the first page directory entry to point to our first page table
    
    ; eax is the pointer to our page table #1
    mov eax, early_page_table_1
    ; and edi is the pointer to our page directory
    mov edi, early_page_directory
    ; now, let's set the first page directory entry to point to our first page table
    and eax, 0xfffff000 ; clear the lower 12 bits
    or eax, 0x3 ; set the present and rw bits
    mov [edi], eax

    ; now, let's set the 184th page table entry to point to VRAM
    ; edi is now the pointer to our page table #1
    ; eax is the pointer to VRAM
    mov edi, early_page_table_1
    add edi, 184 * 4
    mov eax, 0xb8000
    or  eax, 0x3 ; set the present and rw bits
    mov [edi], eax

    ; now, let's identity map the kernel in the lower half
    ; our starting address is 0x100000
    ; in binary: 0000000000 0100000000 000000000000
    ; pd entry 0, pt entry 256
    ;
    ; in this loop,
    ; - edi will point to our current page table entry
    ; - eax will point to our incrementing count, until it hits 1024
    ; - ecx will point to our current physical address
    ; warmup:
    mov edi, early_page_table_1
    add edi, 256 * 4
    mov eax, 256
    mov ecx, 0x100000
l1pre:
    cmp eax, 1024
    je l1end
    jmp l1run
l1run:
    mov ebx, ecx
    or  ebx, 0x3
    mov [edi], ebx
    jmp l1aft
l1aft:
    inc eax
    add ecx, 0x1000
    add edi, 4
    jmp l1pre
l1end:

    ; now that we've mapped our identity space, let's map ourselves into
    ; the higher half - the address 0xC0100000.
    ; in binary: 1100000000 0100000000 000000000000
    ; pde 768, pte 256
    ; let's point the pde to our second page table
    mov eax, early_page_table_2
    mov edi, early_page_directory
    add edi, 768 * 4
    and eax, 0xfffff000 ; clear the lower 12 bits
    or  eax, 0x3
    mov [edi], eax

    ; same loop design as above
    mov edi, early_page_table_2
    add edi, 256 * 4
    mov eax, 256
    mov ecx, 0x100000
l2pre:
    cmp eax, 1024
    je l2end
    jmp l2run
l2run:
    mov ebx, ecx
    or  ebx, 0x3
    mov [edi], ebx
    jmp l2aft
l2aft:
    inc eax
    add ecx, 0x1000
    add edi, 4
    jmp l2pre
l2end:

    ; set cr3 with our page directory
    mov eax, early_page_directory
    mov cr3, eax
    ; enable paging
    mov eax, cr0
    or eax, 0x80000001 ; protection enable & paging (PE/PG)
    mov cr0, eax

    pop eax ; DO NOT MODIFY THESE REGISTERS, _VIRT_START NEEDS THEM
    pop ebx

    jmp _virt_start

section .phys.bss
resb 8192
early_esp:
align 4096
early_page_directory: resb 4096
early_page_table_1: resb 4096
early_page_table_2: resb 4096

section .phys.data
oversized: db "BUG: kernel is too large to fit within one page table! Aborting.", 0

bits 32

section .multiboot
    dd 0x1BADB002           ; magic number
    dd 0x0                  ; flags
    dd - (0x1BADB002 + 0x0) ; checksum

section .text
    global _start
    extern main             ; from main.c
    extern puts

_start:
    cli                     ; bye bye interrupts
    mov  esp, initial_esp   ; set the stack pointer

    xor  ebp, ebp           ; sets ebp to NULL so the stack walker will stop here,
                            ; the ebp will be pushed by main later on

    ; our state is as follows:
    ; eax - multiboot magic
    ; ebx - multiboot info pointer
    ; the rest: we don't give a fuck.
    ; now we'll push our arguments to main,
    ; which is ebx's pointer to multiboot_info_t.
    ; we're pushing these as arguments
    ; to make our life easier if anything changes in that function (aka
    ; if any function call uses eax/ebx)
    push ebx ; multiboot_info_t *
    push eax ; uint32_t magic
    ; main.c: void main(uint32_t, multiboot_info_t *)
    call main

    push exit_msg
    call puts
    hlt                     ; stop the cpu

section .bss
    resb 8192               ; for stack
initial_esp:                ; stack pointer

section .data
exit_msg:
    db "boot: halting CPU"
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

; TODO: check that we are using multiboot

    xor  ebp, ebp           ; sets ebp to NULL so the stack walker will stop here

; the ebp will be pushed by main later on

    call main               ; from main.c

    push exit_msg
    call puts
    hlt                     ; stop the cpu

section .bss
    resb 8192               ; for stack
initial_esp:                ; stack pointer

section .data
exit_msg:
    db "boot: halting CPU"
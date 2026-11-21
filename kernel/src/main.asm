BITS 16

start:
    xor ax, ax
    mov ss, ax
    mov sp, 0x0ffff
    cld

    mov ax, 0x2000
    mov ds, ax
    mov es, ax

    mov si, message
    call print_str

hang:
    hlt
    jmp hang

%include "display.asm"

message db "Hello from kernel!", 0
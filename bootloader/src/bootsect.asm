BITS 16
CPU 8086
ORG 0x7c00

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ax, 0x8000
    mov ss, ax
    mov sp, 0xf000

    mov [driveno], dl

    mov si, message
    call print_str

hang:
    hlt
    jmp hang

%include "display.asm"

driveno db 0x00
message db "Hello, world!", 13, 10, 0

times 510 - ($ - $$) db 0
dw 0xaa55
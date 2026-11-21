BITS 16

extern kmain_
global _start

segment _TEXT class=CODE align=2 public use16
_start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, stacktop
    cld

    call kmain_

hang:
    hlt
    jmp hang

segment _DATA class=DATA align=2 public use16
segment CONST class=DATA align=2 public use16
segment _BSS class=BSS  align=2 public use16
group DGROUP _TEXT _DATA CONST _BSS

segment _STACK class=STACK align=16 public use16
    resb 1024
stacktop:
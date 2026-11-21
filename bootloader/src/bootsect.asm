; A FAT12 bootsector for BenOS.

BITS 16
ORG 0x7c00

    jmp short start
    nop

oem_label           db "BENBOOT "
bytes_per_sector    dw 512
sectors_per_cluster db 1
reserved_for_boot   dw 1
number_of_fats      db 2
rootdir_entries     dw 224
logical_sectors     dw 2880
media_byte          db 0x0f0
sectors_per_fat     dw 9
sectors_per_track   dw 18
head_count          dw 2
hidden_sectors      dd 0
large_sectors       dd 0
driveno             db 0
signature           db 0x29
volume_id           dd 0x0000
volume_label        db "BENOS"
filesystem          db "FAT12"

start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    mov [driveno], dl

    call clear_screen

    call show_menu

; If we get here then the user decided to load the kernel
    call clear_screen

; Try to load the kernel
    call reset_disk

    mov ax, 19
    call calc_registers_from_logical

    mov si, buffer
    mov bx, ds
    mov es, bx
    mov bx, si
    mov ah, 0x02
    mov al, 14
    int 0x13
    jc disk_error

    mov ax, ds
    mov es, ax
    mov di, buffer

    mov cx, word [rootdir_entries]
    xor ax, ax

find_file:
    xchg cx, dx
    mov si, filename
    mov cx, 11
    rep cmpsb
    je found_file

    add ax, 32
    mov di, buffer
    add di, ax
    xchg dx, cx
    loop find_file

    call disk_error

found_file:
    mov ax, word [es:di + 0x0f]

    add ax, 31
    call calc_registers_from_logical

    mov ax, 0x2000
    mov es, ax
    xor bx, bx
    xor ax, ax
    mov ah, 0x02
    mov al, 1

    int 0x13
    jc disk_error

    mov dl, byte [driveno] ; pass driveno to the kernel
    jmp 0x2000:0x0000

hang:
    hlt
    jmp hang

%include "display.asm"
%include "disk.asm"
%include "menu.asm"

filename        db "KERNEL  BIN"

times 510 - ($ - $$) db 0
dw 0xaa55

buffer:
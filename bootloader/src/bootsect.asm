; A FAT12 bootsector for BenOS.

BITS 16
ORG 0x7c00

    jmp short start
    nop

oem_label           db "BENBOOT "
bytes_per_sector    dw 512
sectors_per_cluster db 1
reserved_for_boot   dw 2
number_of_fats      db 2
rootdir_entries     dw 224
logical_sectors     dw 2880
media_byte          db 0x0f0
sectors_per_fat     dw 9
sectors_per_track   dw 18
head_count          dw 2
hidden_sectors      dd 0
large_sectors       dd 0
driveno             dw 0
signature           db 0x29
volume_id           dd 0x00000000
volume_label        db "BENOS      "
filesystem          db "FAT12   "

start:
    cld
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    mov [driveno], dl

    call clear_screen
    call show_menu

    call reset_disk

    mov bx, 0x7e00
    mov ah, 0x02
    mov al, 1
    xor ch, ch
    mov cl, 2
    xor dh, dh
    mov dl, [driveno]
    int 0x13
    jc disk_error

    jmp stage2

hang:
    hlt
    jmp hang

%include "display.asm"
%include "disk.asm"
%include "menu.asm"

times 510 - ($ - $$) db 0
dw 0xaa55

stage2:
; If we get here then the user decided to load the kernel
    call clear_screen

    mov ax, 20
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
    mov [cluster], ax

    mov ax, 2
    call calc_registers_from_logical
    mov bx, buffer
    mov ah, 0x02
    mov al, 9
    int 0x13
    jc disk_error

    mov ax, 0x2000
    mov es, ax
    xor bx, bx

.next_cluster:
    mov ax, [cluster]
    add ax, 32
    call calc_registers_from_logical
    mov ah, 0x02
    mov al, 1
    int 0x13
    jc disk_error
    add bx, 512

    mov ax, [cluster]
    mov cx, ax
    shr cx, 1
    add cx, ax
    mov si, buffer
    add si, cx
    mov dx, [si]
    test al, 1
    jz .even
    shr dx, 4
    jmp .done

.even:
    and dx, 0x0fff

.done:
    mov [cluster], dx
    cmp dx, 0x0ff8
    jb .next_cluster

    mov dl, byte [driveno] ; pass driveno to the kernel
    jmp 0x2000:0x0000

hang2:
    hlt
    jmp hang2

filename        db "KERNEL  BIN"
cluster         dw 0

times (2 * 512) - ($ - $$) db 0

buffer:
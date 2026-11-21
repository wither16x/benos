%ifndef DISK_ASM_
%define DISK_ASM_

BITS 16

%include "display.asm"

; This subroutine comes from MikeOS.
calc_registers_from_logical:
    push bx
    push ax

    mov bx, ax
    xor dx, dx
    div word [sectors_per_track]
    inc dl
    mov cl, dl
    mov ax, bx

    xor dx, dx
    div word [sectors_per_track]
    xor dx, dx
    div word [head_count]
    mov dh, dl
    mov ch, al

    pop ax
    pop bx

    mov dl, byte [driveno]
    ret

;; disk_error -- Call when a disk operation failed.
 ;
 ; Waits for a key to be pressed and reboots.
disk_error:
    mov si, .message
    call print_str

    xor ah, ah
    int 0x16

    jmp reboot

.message db "Could not read from floppy. Press a key...", 0

;; reset_disk -- Resets the disk
reset_disk:
    push ax

    xor ax, ax
    int 0x13
    jc disk_error

    pop ax
    ret

;; reboot -- Reboots by jumping to the reset vector
reboot:
    jmp 0xffff:0

%endif ; DISK_ASM_
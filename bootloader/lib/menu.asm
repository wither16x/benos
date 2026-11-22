%ifndef MENU_ASM_
%define MENU_ASM_

BITS 16

%include "display.asm"
%include "disk.asm"

show_menu:
    push ax
    push si

    mov si, title
    call print_str
    mov si, option1
    call print_str
    mov si, option2
    call print_str
    mov si, prompt
    call print_str

    xor ah, ah
    int 0x16

    cmp al, 'c'
    je .continue

    cmp al, 'r'
    je .reboot

    call clear_screen
    call show_menu

.continue:
    pop si
    pop ax
    ret

.reboot:
    mov si, rebootmsg
    call print_str

; We do a loop so that we don't have to calculate the time directly
    mov bx, 3
    .wait:
        mov ah, 0x86
        mov cx, 0x000f
        mov dx, 0x4240
        int 0x15
        dec bx
        jnz .wait

    call reboot

title       db "BenBoot", 13, 10, 0
option1     db "c - Continue", 13, 10, 0
option2     db "r - Reboot", 13, 10, 0
prompt      db "> ", 0
rebootmsg   db 13, 10, "Rebooting in 3 seconds...", 0

%endif ; MENU_ASM_
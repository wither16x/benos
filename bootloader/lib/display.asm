%ifndef DISPLAY_ASM_
%define DISPLAY_ASM_

BITS 16

;; print_str -- Display a null-terminated string in BIOS teletype mode
 ;
 ; SI: pointer to base of string
print_str:
    push ax
    push bx
    push si

    mov ah, 0x0e

.next_char:
    lodsb

    test al, al
    jz .done

    int 0x10

    jmp .next_char

.done:
    pop si
    pop bx
    pop ax

    ret

;; clear_screen -- Clear the screen by reseting BIOS text mode.
clear_screen:
    push ax

    xor ah, ah
    mov al, 3
    int 0x10

    pop ax
    ret

%endif ; DISPLAY_ASM_
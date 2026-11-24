BITS 16

extern print_
global handle_interrupt_

segment _TEXT class=CODE align=2 public use16

; Interrupt 0x80
; Services:
; AH = 0x00: display string
;   BX = pointer to base of string to display
handle_interrupt_:
    cmp ah, 0x00
    je display_string

    iret

display_string:
    push bx
    push cx
    push dx
    push si
    push di
    push es

    mov ax, bx
    call print_

    pop es
    pop di
    pop si
    pop dx
    pop cx
    pop bx

    iret
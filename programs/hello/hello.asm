BITS 16
ORG 0x8000

start:
    mov si, message
    call print

    ret

print:
    push ax
    push bx
    push si

    mov ah, 0x0e

.next:
    lodsb
    test al, al
    jz .done
    int 0x10
    jmp .next

.done:
    pop si
    pop bx
    pop ax
    ret

message db "Hello, user program!", 13, 10, 0
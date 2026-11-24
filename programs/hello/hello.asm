BITS 16
ORG 0x8000

start:
    xor ah, ah
    mov bx, message
    int 0x80

    ret

message db "Hello, user program!", 13, 10, 0
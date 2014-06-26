.model small
.stack 100h
.data
    msg db "Message$"
.code
    start:
    mov ax,@data
    mov ds,ax
    mov cx,10 ;loop 10 times
    mov al,'a';start with character 'a'
    call printColoredCharacters
    mov dl,10
    mov dh,20
    call setCursorPosition ; move cursor to dl column, dh line
2
mov dx,offset msg
call printMessage  ;print a string at current position
HLT
proc printColoredCharacters
    loop1:
        mov bx,cx  ;cx is modified inside of next function
        call writeCharacterWithAttribute
        inc dl
        call setCursorPosition
        inc al  ;next character
        mov cx,bx   ;restore cx
    loop loop1
    ret
endp printColoredCharacters
proc printMessage
    mov ah,9
    int 21h
endp printMessage
;DX contains the address of the message
;BIOS function for output of a string,
;terminated with '$', at DS:DX
proc setCursorPosition  ;dl - column
     mov ah,2           ;dh - row
     int 10h            ;bh - page number
     ret
endp setCursorPosition
proc writeCharacterWithAttribute  ;al - character to display
     mov ah,09h
     mov bh, 0
     mov cx, 1
     int 10h
     ret
endp writeCharacterWithAttribute
;bl - atribute
;bh - disable blinking
;cx - number of times to write
;a character
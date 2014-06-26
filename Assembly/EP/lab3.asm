.model small
.stack 100h
.data
mesaj db "Introduceti un caracter:",0
length equ $
.code start:
    mov ax,@data
    mov ds,ax
loop1:
      mov cx,[length]
      mov bx,offset mesaj
      call putstring
      xor al,al
      call getcharWithoutEcho
      cmp al,'E'
      ;call putchar
      jne loop1
HLT
    proc getcharWithoutEcho ;stores the char into al
        mov ah, 08h
int 21h
        ret
    endp getcharWithoutEcho
    proc putchar    ;al  contains the character to write
       mov ah,0Eh  ;write a character, advance the cursor, scroll if necessary
       int 10h
       ret
endp putchar
    proc putstring  ;cx contains the stringLength
         xor di,di   ;bx contains the address of the string
8
loop3:
        mov al,bx[di]
        call putchar
        inc di
loop loop3
     ret
endp putstring
end start
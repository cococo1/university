.model small
.stack 100h
.data
    msg1 db "Hello$"
    l1 db 5
    msg2 db "Salut$"
    l2 db 5
    msg3 db "Privet$"
    l3 db 6
    msg4 db "Holla$"
    l4 db 5
.code start:
    mov ax,@data
    mov ds,ax
    xor cx,cx
    mov bx,0000_1010b  ;string attributes: background color_text color
    mov cl,l1          ;string length
    mov bp, offset msg1;location of string
    call writeString
    mov bx,1001_1101b
    mov cl,l2
    mov dh,1
    mov bp, offset msg2
    call writeString
    mov bx,1110_1100b
    mov cl,l3
    mov dh,2
    mov bp, offset msg3
    call writeString
    mov bx,1111_0100b
    mov cl,l4
4
mov dh,3
mov bp, offset msg4
call writeString
call toggleIntensity
HLT
proc delay
    mov ah,86h ;BIOS wait function
    mov cx,10h ; cx:dx - interval in microseconds
    int 15h
    ret
endp delay
proc toggleIntensity   ;blinking not available on emulator
    loop1:
        mov ax,1003h ;BIOS toggle intensity/blinking function
        mov bx,0000h ;BL - write mode: 0 - enable intensive colors
        int 10h      ; BH - to avoid problems on some adapters
        call delay
        mov ax,1003h
        mov bx,0001h  ;BL=1  - enable blinking
        int 10h
        call delay
    loop loop1
     ret
 endp toggleIntensity
proc writeString ;
    mov al,1   ; if bit 1 then string contains attributes
    push ds
    pop es     ; ES:BP points to the string to be printed
    mov ah,13h ;BIOS function for writing a string
5
int 10h
    ret
endp writeString
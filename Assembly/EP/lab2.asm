.model small
.stack 100h
.data
string db "comunicatie despre introducerea informatiei",0
stringLength equ $
string1 db 256 DUP(?)
string1Length dw 256
filename db "file.txt",0
2
filehandle dw ?
cxCopy dw ?
bxCopy dw ?
dxCopy dw ?
c db ? ;a character which is stored while reading from file
.code start:
mov ax,@data
        mov ds,ax
;Write a message on the screen
        mov cx,[stringLength]
        mov bx,offset string
        call putstring
;Get a string:
        mov cx,[string1Length]
        mov bx,offset string1
;from keyboard:
        call getstringFromKeyboard
;from a file:
        ;call getStringFromFile
        mov [string1Length],di
;Set the cursor position
        mov dl,0
        mov dh,1
        mov bh,0
        call setCursorPosition
;Output goes to screen
        mov cx,[string1Length]
        mov bx,offset string1
        call putstring
;Output goes to a new created file
        ;call createFile
        ;mov cx,[string1Length]
        ;lea dx,string1
        ;call writeToFile
        ;call closeFile
;Output appends to an existent file
3
;call openFile
;mov al, 2  ;set the pointer to end position
;call moveFilePointer
;mov cx,[string1Length]
;lea dx,string1
;call writeToFile
;call closeFile
HLT
proc putchar    ;al  contains the character to write
    mov ah,0Eh  ;write a character, advance the cursor, scroll if necessary
    int 10h
    ret
endp putchar
proc getchar   ;al contains the character that was read
    mov ah,00h ;get keystroke from keyboard (no echo)
    int 16h
    call upcaseChar
    ret
endp getchar
proc getstringFromKeyboard ;cx contains the stringLength
    xor di,di  ;bx contains the address of the string
    loop1:     ;di will contain length of read string
        call getchar
        call putchar
        cmp al,0dh
        je enterPressed
        mov bx[di],al
        inc di
    loop loop1
enterPressed:
;ENTER pressed
    ret
endp getstringFromKeyboard
proc readCharFromFile
4
    mov ah, 3Fh  ;read from file
    mov bx, [filehandle]
    mov cx,1
    mov dx, offset c
    int 21h
    cmp ax,0      ;EOF reached
    je EOFReached
    mov al,c ;store the read character
    call upcaseChar
    ret
EOFReached:
    mov al,0dh
    ret
endp readFromFile
proc getstringFromFile ;cx contains the stringLength
    call openFile      ;bx contains the address of the strin
                       ;di will contain length of read string
    mov al, 0  ;set the pointer to start position
    mov cxCopy, cx
    mov dxCopy, dx
    mov bxCopy,bx
    call moveFilePointer
    mov cx,cxCopy
    mov dx,dxCopy
    mov bx,bxCopy
    xor di,di
    loop2:
        mov cxCopy,cx
        mov dxCopy,dx
        mov bxCopy,bx
        call readCharFromFile
        mov cx,cxCopy
        mov dx,dxCopy
        mov bx,bxCopy
        call putchar
        cmp al,0dh
        je EOFReached1
        mov bx[di],al
        inc di
    loop loop2
EOFReached1:
;EOF reached
5
    ret
endp getstringFromFile
proc putstring  ;cx contains the stringLength
    xor di,di   ;bx contains the address of the string
    loop3:
        mov al,bx[di]
        call putchar
        inc di
loop loop3
    ret
endp putstring
proc createFile
    mov ah, 3ch
    mov cx, 0
    lea dx, filename  ;point to filename
    int 21h
    jc errorCreate
    mov [filehandle], ax
errorCreate:
    ret
endp createFile
proc writeToFile
    mov bx, [filehandle] ;cx contains the stringLength
    mov ax, 4000h  ; write to file function
    int 21h        ;do it
    ret
endp writeToFile
proc openFile
    lea dx, filename
    mov ah,3dh
    mov al,2
    int 21h
    jc errorOpen
    mov [filehandle], ax
errorOpen:
;point to filename
;open file function
;open for writing/reading
;do it
 ;create file func.
;file atribute
;do it
;dx points to the data to write
6
ret
        endp openFile
        proc moveFilePointer     ;al indicates the position:0,1,2
            mov bx, [filehandle]
            mov ah, 42h
            xor cx,cx  ;don't move!
            xor dx,dx
            ;mov dx,[fileposition] ;move to the end position
            int 21h
            ret
        endp moveFilePointer
        proc closeFile
            mov bx, [filehandle]
            mov ax, 3eh ;close file
            int 21h
            ret
        endp closeFile
        proc setCursorPosition ;dl - column
            mov ah,2           ;dh - row
            int 10h            ;bh - page number
            ret
        endp setCursorPosition
        proc upcaseChar ;al contains the character
            cmp al,61h ;61h - 'a'
            jl notLowercaseLetter
            cmp al,7Ah ;7ah - 'z'
            jg notLowercaseLetter
            sub al,32D
       notLowercaseLetter: ;so, we do not need to upcase it
            ret
        endp upcaseChar
end start
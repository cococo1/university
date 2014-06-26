.model small
.stack 100h
.data
    cxInitial dw ?
    dxInitial dw ?
.code
start:
    mov al,13h
    call setVideoMode
    mov al,1011b
    mov bx, 40
    mov cx, 140
    mov dx,80
    call drawRect
2
HLT
proc setVideoMode ;al video mode
    mov ah,0
int 10h
    ret
endp setVideoMode
proc changePixelColor
    ;al pixel color
    ;cx - column
    ;dx - row
    mov ah, 0Ch
    int 10h
    ret
endp changePixelColor
proc drawRect
    ;bx - rect size
    ;al - color
    ;cx - initial x
    ;dx - initial y
    mov cxInitial,cx
    mov dxInitial,dx
    add dx,bx
    loop1:
        add cx,bx
        loop2:
            call changePixelColor
            dec cx
            cmp cxInitial,cx
            jl loop2
        dec dx
        cmp dxInitial,dx
        jl loop1
        ret
endp drawRect
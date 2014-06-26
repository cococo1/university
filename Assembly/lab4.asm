.model small
.stack 100h
.data
    x dw 1234h
    z dw 3456h
    y dw ?
.code 
    start:
        mov ax, data
        mov ds, ax
        
    ;to divide z/2 we can use shifts
    mov ax, z ;store the initial value of z
    sar z,1
    clc ;before comparing we clear CF
    mov dx,x
    cmp dx,z
    jge case2
    case1: ; z/2 > x
        sar x,1 ;x/2
        clc
        add ax,x ;in ax we have z
        adc ax,0
        sub ax,65
        sbb ax,0
        mov y,ax    
        jmp exit
    case2: ;z/2 <= x
        sal ax,1 ; 2*z
        clc
        sub ax,32
        sbb ax,0
        mov y,ax

    exit: end start    
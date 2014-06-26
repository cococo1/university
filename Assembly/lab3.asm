;Variant 7: x[i]=x[i-1]+5a*b
.model small
.stack 100h
.data
    x dw 6 dup(?)
    a db 3h
    b db 5h
    avg dw ?
    length db 5
.code
    start:
        mov ax, data
        mov ds,ax
        
    ;first compute 5a*b because its a const
    ;assume 5*a*b is at most a DW
        mov al,5
        mul a   ;result is still in al
        mul b   ;result is in ax
        
                    
        
        ;we'll take the first element=1
        mov x[0], 1                    
        mov di,2 ;index of array
        mov si,0 ;index-1
        mov cx,word ptr length 
        mov avg,0
        
        loop1:
            mov dx,x[si]
            mov x[di],dx ;x[i]=x[i-1]
            add x[di],ax ;add the expression
            adc x[di],0
            mov dx,x[di]
            add avg,dx ;compute the avg
            adc avg,0  
            inc di
            inc di
            inc si
            inc si     
            loop loop1
        mov ax,avg
        div length
        ;cbw
        mov avg,ax   
        
     end start 
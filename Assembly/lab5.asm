.model small
.stack 100h
.data
    x dw 1,2,3,4,5,6,7,8,9,10
    y dw 10 dup(?)
    sum dw ?
    n db 10
    
.code
    start:
        mov ax,data
        mov ds,ax
                      
        mov bx,word ptr n
        lea di,x
        CALL computeSum
        mov sum,dx

        ;prepare for procedure call
        lea di,x
        lea si,y
        mov bx,word ptr n 
        clc
        cmp sum,0
        jge case2
        case1: ;Generate a substring with odd numbers

            call oddNumbersSubstring
        
        
            jmp exit
        case2: ;generate a substring with even numbers
            call evenNumbersSubstring
        
        
        
        exit:
        
        HLT
        
       
       ;procedures:
       
    computeSum proc
    ;computes the sum of an array.
    ;takes the address of the first element
    ;from di and the number of elements from bx
    ;stores the result in dx
        mov cx,bx
        mov dx,0
        loop1: 
         add dx,[di]
          adc dx,0
          inc di
          inc di
        loop loop1
        ret
        computeSum endp    
    
    oddNumbersSubstring proc
    ;takes the address of input array in di
    ;takes the address of output array in si
    ;takes the number of elements in input array
    ;in bx
    ;the output array will be filled with odd
    ;numbers
    
    mov cx,bx
    
    loop2:
        mov ax,[di]
        clc
        shr ax,1 ;in CF will be the LSB.
                 ; if it is 1 => odd
        jnc notOddNumber
           mov dx,[di]
           mov [si],dx
           inc si
           inc si
        notOddNumber:
           inc di
           inc di          
    loop loop2
    ret
    oddNumbersSubstring endp
        
    evenNumbersSubstring proc
    ;takes the address of input array in di
    ;takes the address of output array in si
    ;takes the number of elements in input array
    ;in bx
    ;the output array will be filled with even
    ;numbers
    
    mov cx,bx
    
    loop3:
        mov ax,[di]
        clc
        shr ax,1 ;in CF will be the LSB.
                 ; if it is 0 => even
        jc notEvenNumber
           mov dx,[di]
           mov [si],dx
           inc si
           inc si
        notEvenNumber:
           inc di
           inc di          
    loop loop3
    ret
    evenNumbersSubstring endp      
    
         
.data
    x db ?   ;data byte 11h
    y dw ?   ;data word 2222h
    z dd ?   ; double data word 33334444h
    disp dw 3a06h
    
.stack 100h

.code
start:
    ;set segment registers:
    mov ax,@data
    mov ds,ax
    
    ;set smth. into the registers:
    ;this is the immediate addressing mode:
    mov al,11h
    mov ah,0
    mov bx,2222h
    mov cx,3333h
    mov dx,4444h
    
    ;set the variables:
    mov x,al
    mov y,bx
    mov [z+2],cx
    mov z,dx    
    
    ;store the content of the
    ; registers to stack:   
    push ax
    push bx
    push cx
    push dx
    
    ;reset the registers:
    xor ax,ax
    xor bx,bx
    xor cx,cx
    xor dx,dx
    
    ;pop the content back into registers:
    pop dx
    pop cx
    pop bx
    pop ax  
          
    ;store data from ax to es:
    mov es,ax
    ;now change ax to needed address for ds:
    mov ax,3a06h                    
    
    mov ds,ax;data segment reset to 3A06H
    ;now restore ax:
    mov ax,es
            
;ADDRESSING MODES:

    ;1. Direct addressing mode 
    ;(displacement only)            
    mov [0h],ax
    ;or :
    mov y,bx
    ;or:
    mov ds:[3h],cx
    mov [z+2],dx
    
    ;reset the registers:
    xor ax,ax
    xor bx,bx
    xor cx,cx
    xor dx,dx
    
    ;restore data into registers:
    ;2. Register indirect addressing mode: 
    ;first, set the offset:
    mov bx,0h
    mov al,[bx]
    
    ;use di:
    mov di,1h  
    mov bx,[di]
    
    ;use si:
    mov si,3h
    mov cx,[si]
    
    inc si
    inc si
    
    mov dx,[si] 
    
    ;Now we will write to memory in a
    ;different order:
    
    ;3. Base addressing mode:
    ;we'll use bx:
    mov bx, 0h  
    ;ds is the displacement:  
    mov ds[bx],dx 
    inc bx
    inc bx
    mov [ds+bx],cx
    ;al will be the "(bx+2)th element of array"
    mov [bx+2],al   
    
    ;reset again the registers:
    xor ax,ax
    xor cx,cx
    xor dx,dx
    
    ;4. Indexed addressing mode: 
    ;ds is our "array" 
    ;our index for al:
    mov si,4
    mov al,ds[si]
    mov di,2
    mov cx,ds[di]
    dec di
    dec di
    mov dx,ds[di]
    
    ;5. Based indexed addressing mode:
    mov bx,0h
    mov si,0h
    mov [bx][si],al
    inc si
    mov [bx][si],cx
    inc bx
    inc si
    mov [si][bx],dx
    
    ;reset again the registers:
    xor ax,ax
    xor cx,cx
    xor dx,dx 
    
    ;6. Based indexed plus displacement
    ;addressing mode:
    ;ds is the disp.
    mov bx,0h
    mov di,0h
    mov al,ds[bx][di]
    inc di
    mov cx,ds[bx+di]
    inc di
    inc bx
    mov dx,[ds+bx+di]
    mov ax,[ds][bx][di]
    
     
              
    
    
    
    
    
    
    
    
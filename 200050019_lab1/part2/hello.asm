mov ah, 0x0e ; set tele-type mode (output to screen)
mov al, ’H’ ; one ascii character hex code in register AL
int 0x10 ; send content of register to screen via an interrupt

mov ah, 0x0e ; 
mov al, ’E’ ; 
int 0x10 ; 

mov ah, 0x0e ; 
mov al, ’E’ ; 
int 0x10 ; 

mov ah, 0x0e ; 
mov al, ’L’ ; 
int 0x10 ; 

mov ah, 0x0e ; 
mov al, ’L’ ; 
int 0x10 ;

mov ah, 0x0e ; 
mov al, ’0’ ; 
int 0x10 ;  
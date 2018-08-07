%include "io.inc"

section .data
    %include "input.inc"

    rev_nums times 100 dd 0
    rev_base times 100 dd 0

section .text
global CMAIN

print_char:                    ; daca avem un caracter.. 
    add ebx, 'a'-10            ;..mai mare ca 9..  
    PRINT_CHAR ebx             ;..pe scara ascii
    
    dec ecx
    cmp ecx, 0                 ; nu a fost ultimul element din vector
    je continue                
    
    jmp print

baza_incorecta:                     ; ajungem aici daca base<1 || base>16  
    PRINT_STRING "Baza incorecta"        
    NEWLINE
    dec ecx
    cmp ecx, 0                      ; am terminat vectorul
    je final                        ;
    
    jmp next_number                 ; trecem la urmatorul nr din vector

CMAIN:
    mov ebp, esp; for correct debugging
    xor ecx,ecx
    xor eax, eax
    mov ecx, dword [nums]


rev_nums_push:                
    push dword [nums_array+ 4*(ecx-1)]  ; punem pe stiva ultimul elem din nums 
    loop rev_nums_push                  ; si tot asa pana ecx devine 0                                        
    
    xor eax, eax                        ; eax=0
    mov ecx, [nums]                     ; ecx=nums

rev_nums_pop:                           ; punem de pe stiva in rev_nums
    pop dword [rev_nums+(ecx-1)*4]
    loop rev_nums_pop
    
    xor eax, eax                        ; eax=0                   
    mov ecx, [nums]                     ; ecx=numes

rev_base_push:                          ; punem pe stiva elementele..
    push dword [base_array+ 4*(ecx-1)]  ;..din base
    loop rev_base_push
    
    xor eax, eax                         
    mov ecx, [nums]

rev_base_pop:                           ; punem de pe stiva..
    pop dword [rev_base+(ecx-1)*4]      ;..in rev_base
    loop rev_base_pop
    
    xor ebx, ebx
    xor ecx,ecx     ; ecx=0  
    mov ecx, [nums] ; use ecx as counter(contor mare)...
                    ;...ecx=nums

next_number: 
    xor ebx, ebx
    xor eax,eax
    mov eax, dword [rev_nums + 4*(ecx-1)] 

impartiri:   
    xor edx, edx    ; edx = 0, ca sa mearga
    cmp dword [rev_base + 4*(ecx-1)], 2     ; daca e mai mic ca 2..
    jl baza_incorecta                       ;..sari
    
    cmp dword [rev_base + 4*(ecx-1)],16     ; daca e mai mare ca 16..
    jg baza_incorecta                       ;..sari
    
    div dword [rev_base + 4*(ecx-1)]  ; eax=eax/corespondentul... 
                                        ;...din vectorul de baze
    inc ebx         ; incrementam un contor(mic) care sa ne ajute la..
                    ;..printarea numerelor
    push edx        ; punem pe stiva restul 
    cmp eax,0       ; daca catul ajunge 0, ne oprim
    jne impartiri
    
    xor eax, eax    ;eax=0   
    mov eax,ecx         ; punem ecx in eax
    mov ecx, ebx    ; punem contorul mic pe ecx pentru moment   

print:             
    pop ebx         ; scoatem ce avem pe stiva
    cmp ebx, 9      ; verificam daca este mai mare ca 9
    jg print_char    
    add ebx, '0'    ;daca nu, il printam cum e
    PRINT_CHAR ebx 
    loop print
    

continue:
    NEWLINE
    
        
    mov ecx, eax    ; punem din nou contorul mare pe ecx        
    dec ecx         ; nu imi mergea cu loop
    cmp ecx, 0      ; asa ca l-am decrementat
    jne next_number

final:              ;pentru cazul in care ultima baza e incorecta    

    xor eax, eax
    ret
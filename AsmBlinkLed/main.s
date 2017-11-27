    PRESERVE8
    THUMB
    GET		  config.s
    GET       stm32f10x.s    

    AREA      RESET, CODE, READONLY

    DCD       STACK_TOP
    DCD       Reset_Handler

    ENTRY

Reset_Handler    PROC
    EXPORT    Reset_Handler

main
    MOV32     R0, 0x20000200		; R0 - array start (arr)
    MOV       R1, #50     			; R1 - array size (size)
    MOV       R2, #0                ; R2 - array position (pos)
    MOV       R3, R1                ; R3 - half of array size (half_size)
    ASR       R3, #1                ; R3 == 25

loop
	CMP       R2, R3                ; while (pos != half_size)
	BLNE 	  swap
	
	B         loop

    ENDP

swap          PROC
	;  l-->         <--r  - left and right positions (l, r)
	; [0 1 2 3 ... 48 49] - array
    MOV       R4, R0 				; R4 - address of l
    MOV       R5, R2 				; R5 == pos
    LSL       R5, #3 				; R5 == pos * 8
    ADD       R4, R5 				; R4 == arr + pos * 8

    MOV       R5, R0 				; R5 - address of r
    MOV       R6, R1 				; R6 == size
    SUB       R6, R2 				; R6 == size - pos
    SUB       R6, #1 				; R6 == size - pos - 1
    LSL       R6, #3 				; R6 == (size - pos - 1) * 8
    ADD       R5, R6 				; R5 == arr + (size - pos - 1) * 8

    LDR       R6, [R4] 				; R6 - l
    LDR       R7, [R5] 				; R7 - r

	MOV		  R8, R6   				; R8 - tmp, R8 == l
	BFI 	  R6, R7, #0, #8 		; l = r
	BFI 	  R7, R8, #0, #8 		; r = l		
    STR       R6, [R5] 				; *(address of r) = l  
    STR       R7, [R4] 				; *(address of l) = r

    ADD       R2, #1   				; pos++
	
	BX		  LR
    ENDP
 
    END
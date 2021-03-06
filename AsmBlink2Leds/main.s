	PRESERVE8							; 8-битное выравнивание стека
	THUMB								; Режим Thumb (AUL) инструкций

	GET	config.s						; include-файлы
	GET	stm32f10x.s	

	AREA RESET, CODE, READONLY

	; Таблица векторов прерываний
	DCD STACK_TOP						; Указатель на вершину стека
	DCD Reset_Handler					; Вектор сброса

	ENTRY								; Точка входа в программу

Reset_Handler	PROC					; Вектор сброса
	EXPORT  Reset_Handler				; Делаем Reset_Handler видимым вне этого файла

main									; Основная подпрограмма
	MOV32	R0, PERIPH_BB_BASE + \
			RCC_APB2ENR * 32 + \
			4 * 4						; вычисляем адрес для BitBanding 4-го бита регистра RCC_APB2ENR
										; BitAddress = BitBandBase + (RegAddr * 32) + BitNumber * 4
	MOV		R1, #1						; включаем тактирование порта D (в 4-й бит RCC_APB2ENR пишем '1`)
	STR 	R1, [R0]					; загружаем это значение
	
	MOV32	R0, GPIOC_CRH				; адрес порта
	MOV		R1, #0x33					; 2-е 4-битных маски настроек для Output mode 50mHz, Push-Pull ("00110011")
	LDR		R2, [R0]					; считать порт
    BFI		R2, R1, #0, #8    			; скопировать биты маски в позицию PIN8-PIN9
    STR		R2, [R0]					; загрузить результат в регистр настройки порта
	
	
	
	MOV32	R0, PERIPH_BB_BASE + \
			RCC_APB2ENR * 32 + \
			2 * 4						; вычисляем адрес для BitBanding 4-го бита регистра RCC_APB2ENR
										; BitAddress = BitBandBase + (RegAddr * 32) + BitNumber * 4
	MOV		R1, #1						; включаем тактирование порта D (в 4-й бит RCC_APB2ENR пишем '1`)
	STR 	R1, [R0]					; загружаем это значение
	
	MOV32	R0, GPIOA_CRL				; адрес порта
	MOV		R1, #0x8					; 2-е 4-битных маски настроек для Output mode 50mHz, Push-Pull ("00110011")
	LDR		R2, [R0]					; считать порт
    BFI		R2, R1, #0, #4    			; скопировать биты маски в позицию PIN8-PIN9
    STR		R2, [R0]					; загрузить результат в регистр настройки порта
	MOV		R10, #0

loop									; Бесконечный цикл
	MOV32	R0, GPIOC_BSRR				; адрес порта выходных сигналов
	MOV32   R1, GPIOA_IDR
	
	LDR		R2, [R1]
	MOV		R3, #0
	BFI		R3, R2, #0, #1

	CMP		R3, #0
	IT		NE
	BLNE	ledon

	BL		delay
	B		loop						; возвращаемся к началу цикла
	
	ENDP

delay		PROC						; Подпрограмма задержки
	PUSH	{R0}
	MOV32	R0, 0x30000; Загружаем в стек R0, т.к. его значение будем менять
	;LDR		R0, =DELAY_VAL				; псевдоинструкция Thumb (загрузить константу в регистр)
delay_loop
	SUBS	R0, #1						; SUB с установкой флагов результата
	IT 		NE
	BNE		delay_loop					; переход, если Z==0 (результат вычитания не равен нулю)
	POP		{R0}						; Выгружаем из стека R0
	BX		LR							; выход из подпрограммы (переход к адресу в регистре LR - вершина стека)
	ENDP	
	
ledon		PROC	
	MOV32	R8, PIN8 :OR: (PIN9 << 16)
	MOV32	R9, PIN9 :OR: (PIN8 << 16)
	
	CMP		R10, #0
	ITTE	EQ
	MOVEQ	R10, #1
	STREQ	R8, [R0]
	MOVNE	R10, #0
	STRNE	R9, [R0]


	BX		LR
	ENDP

    END

#include "stdbool.h"
#include "stm32f10x.h"
#include "string.h"

#define DELAY_CYCLES 500000
#define	USART_BUFF_SIZE	256

void delay(uint32_t cycles);
void executeCommand(void);
void initButton(void);
void initOutputPorts(void);
void initTimer(void);
void initUSART2(void)
void setNumber(uint32_t i);
void transmitString(char * str);

uint32_t current_number = 0;
bool started = 0;
bool com_received = 0;

char receive_buffer[USART_BUFF_SIZE];	// Буфер приёма USART
char transmit_buffer[USART_BUFF_SIZE];	// Буфер передачи USART

void setNumber(uint32_t i)
{
	switch(i)
	{
		case 0:
			GPIOA->BSRR |= GPIO_BSRR_BR0;
			GPIOA->BSRR |= GPIO_BSRR_BS1;
			GPIOA->BSRR |= GPIO_BSRR_BS2;
			GPIOA->BSRR |= GPIO_BSRR_BS3;
			GPIOA->BSRR |= GPIO_BSRR_BS4;
			GPIOA->BSRR |= GPIO_BSRR_BS5;
			GPIOA->BSRR |= GPIO_BSRR_BS6;
			break;
		case 1:
			GPIOA->BSRR |= GPIO_BSRR_BR0;
			GPIOA->BSRR |= GPIO_BSRR_BR1;
			GPIOA->BSRR |= GPIO_BSRR_BR2;
			GPIOA->BSRR |= GPIO_BSRR_BR3;
			GPIOA->BSRR |= GPIO_BSRR_BS4;
			GPIOA->BSRR |= GPIO_BSRR_BS5;
			GPIOA->BSRR |= GPIO_BSRR_BR6;
			break;
		case 2:
			GPIOA->BSRR |= GPIO_BSRR_BS0;
			GPIOA->BSRR |= GPIO_BSRR_BR1;
			GPIOA->BSRR |= GPIO_BSRR_BS2;
			GPIOA->BSRR |= GPIO_BSRR_BS3;
			GPIOA->BSRR |= GPIO_BSRR_BR4;
			GPIOA->BSRR |= GPIO_BSRR_BS5;
			GPIOA->BSRR |= GPIO_BSRR_BS6;
			break;
		case 3:
			GPIOA->BSRR |= GPIO_BSRR_BS0;
			GPIOA->BSRR |= GPIO_BSRR_BR1;
			GPIOA->BSRR |= GPIO_BSRR_BR2;
			GPIOA->BSRR |= GPIO_BSRR_BS3;
			GPIOA->BSRR |= GPIO_BSRR_BS4;
			GPIOA->BSRR |= GPIO_BSRR_BS5;
			GPIOA->BSRR |= GPIO_BSRR_BS6;
			break;
		case 4:
			GPIOA->BSRR |= GPIO_BSRR_BS0;
			GPIOA->BSRR |= GPIO_BSRR_BS1;
			GPIOA->BSRR |= GPIO_BSRR_BR2;
			GPIOA->BSRR |= GPIO_BSRR_BR3;
			GPIOA->BSRR |= GPIO_BSRR_BS4;
			GPIOA->BSRR |= GPIO_BSRR_BS5;
			GPIOA->BSRR |= GPIO_BSRR_BR6;
			break;
		case 5:
			GPIOA->BSRR |= GPIO_BSRR_BS0;
			GPIOA->BSRR |= GPIO_BSRR_BS1;
			GPIOA->BSRR |= GPIO_BSRR_BR2;
			GPIOA->BSRR |= GPIO_BSRR_BS3;
			GPIOA->BSRR |= GPIO_BSRR_BS4;
			GPIOA->BSRR |= GPIO_BSRR_BR5;
			GPIOA->BSRR |= GPIO_BSRR_BS6;
			break;
		case 6:
			GPIOA->BSRR |= GPIO_BSRR_BS0;
			GPIOA->BSRR |= GPIO_BSRR_BS1;
			GPIOA->BSRR |= GPIO_BSRR_BS2;
			GPIOA->BSRR |= GPIO_BSRR_BS3;
			GPIOA->BSRR |= GPIO_BSRR_BS4;
			GPIOA->BSRR |= GPIO_BSRR_BR5;
			GPIOA->BSRR |= GPIO_BSRR_BS6;
			break;
		case 7:
			GPIOA->BSRR |= GPIO_BSRR_BR0;
			GPIOA->BSRR |= GPIO_BSRR_BR1;
			GPIOA->BSRR |= GPIO_BSRR_BR2;
			GPIOA->BSRR |= GPIO_BSRR_BR3;
			GPIOA->BSRR |= GPIO_BSRR_BS4;
			GPIOA->BSRR |= GPIO_BSRR_BS5;
			GPIOA->BSRR |= GPIO_BSRR_BS6;
			break;
		case 8:
			GPIOA->BSRR |= GPIO_BSRR_BS0;
			GPIOA->BSRR |= GPIO_BSRR_BS1;
			GPIOA->BSRR |= GPIO_BSRR_BS2;
			GPIOA->BSRR |= GPIO_BSRR_BS3;
			GPIOA->BSRR |= GPIO_BSRR_BS4;
			GPIOA->BSRR |= GPIO_BSRR_BS5;
			GPIOA->BSRR |= GPIO_BSRR_BS6;
			break;
		case 9:
			GPIOA->BSRR |= GPIO_BSRR_BS0;
			GPIOA->BSRR |= GPIO_BSRR_BS1;
			GPIOA->BSRR |= GPIO_BSRR_BR2;
			GPIOA->BSRR |= GPIO_BSRR_BS3;
			GPIOA->BSRR |= GPIO_BSRR_BS4;
			GPIOA->BSRR |= GPIO_BSRR_BS5;
			GPIOA->BSRR |= GPIO_BSRR_BS6;
			break;
		default:
			break;
	}
}

void initOutputPorts(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	

	GPIOA->CRL = 0;
	GPIOB->CRL = 0;
	GPIOA->CRL |= GPIO_CRL_MODE0_1;
	GPIOA->CRL |= GPIO_CRL_MODE1_1;
	GPIOB->CRL |= GPIO_CRL_MODE0_1;
	GPIOB->CRL |= GPIO_CRL_MODE1_1;
	GPIOA->CRL |= GPIO_CRL_MODE4_1;
	GPIOA->CRL |= GPIO_CRL_MODE5_1;
	GPIOA->CRL |= GPIO_CRL_MODE6_1;
}

void EXTI2_IRQHandler(void)
{
	delay(DELAY_CYCLES);

	setNumber(0);
	current_number = 0;
	
	EXTI->PR |= EXTI_PR_PR2; // Сбрасываем флаг прерывания установкой бита в '1'
}

// Инициализация прерывания по кнопке PC2
void initButton(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
	
	GPIOC->CRL = 0;
	GPIOC->CRL |= GPIO_CRL_CNF2_1;
	GPIOC->BSRR |= GPIO_BSRR_BS2;
	
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI2_PC; // Регистрация порта PC2 как входных данных для прерывания
	
	EXTI->FTSR |= EXTI_FTSR_TR2;   			  // Прерывание по спаду импульса (при нажатии на кнопку)
	EXTI->IMR |= EXTI_IMR_MR2;     			  // Активация прерывания по 2 линии (PA2, ..., PG2)
	
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_SetPriority(EXTI2_IRQn, 0);
}

void TIM6_DAC_IRQHandler(void)
{
	TIM6->SR &= ~TIM_SR_UIF; // Сброс флага переполнения

	if (started)
	{
		setNumber(current_number);

		current_number++;
		if (current_number == 10)
			current_number = 0;
	}
}

// Инициализация прерывания по таймеру TIM6
void initTimer(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	
	TIM6->PSC = 24000; 			// Предделитель частоты (24кГц / 24000 = 1кГц - частота таймера)
	TIM6->ARR = 1000;  			// Модуль счёта таймера (1кГц / 1000 = 1с - время до переполнение счетчика)
	TIM6->DIER |= TIM_DIER_UIE; // Разрешить прерывание по переполнению счетчика
	TIM6->CR1 |= TIM_CR1_CEN; 	// Включить таймер

	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	NVIC_SetPriority(TIM6_DAC_IRQn, 1);
}

void USART2_IRQHandler(void)
{
	char ch;

	if ((USART2->SR & USART_SR_RXNE) != 0)	// Received data is ready to be read
	{
		ch = USART2->DR;                   	// Считываем пришедший байт
		if (ch == 0x0D)				    	// Если это символ конца строки ('\r')
		{
			com_received=true;
			return;
		}
		receive_buffer[strlen(receive_buffer)] = ch;
	}
}

// Инициализация прерывания по USART2 интерфейсу
void initUSART2(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);	// PA2 на выход
	GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1);
	
	GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);	// PA3 на вход
	GPIOA->CRL |= GPIO_CRL_CNF3_0; 						// Плавающий вход
	
	/*
	Скорость передачи данных - 19200
	Частота шины APB1 - 24МГц
	
	1. USARTDIV = 36000000 / (16 * 19200) = 78.125
	2. 117 = 0x4E
	3. 16 * 0.125 = 2
	4. Итого 0x4E2
	*/
  	USART2->BRR = 0x4E2;  // Baud rate register: 3 бита - целая часть, 1 бит - дробная часть
	
	USART2->CR1 = 0;	
	USART2->CR2 = 0;
	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; // Receiver enable, Transmitter enable, USART enabled 
	USART2->CR1 |= USART_CR1_RXNEIE;						   // Разрешить прерывание по приему байта данных
	
	NVIC_EnableIRQ(USART2_IRQn);
}

void executeCommand(void)
{
	memset(transmit_buffer, 0, USART_BUFF_SIZE);
	
	if (!strcmp(receive_buffer, "*IDN?"))
	{
		strcat(transmit_buffer, "Golubev Pavel, Nikitin Makar, IU4-71");
		transmitString(transmit_buffer);
	}
	else if (!strcmp(receive_buffer, "START"))
	{
		started = 1;
	}
	else if (!strcmp(receive_buffer, "STOP"))
	{
		started = 0;
	}

	memset(receive_buffer, 0, USART_BUFF_SIZE);
	com_received = false;
}

int main(void)
{
	initOutputPorts();
	initButton();
	initTimer();
	initUSART2();
	
	while(true)
	{
		if (com_received)
			executeCommand();
	}
}

void delay(uint32_t cycles)
{
    uint32_t i;
    for (i = 0; i < cycles; i++)
        ;
}

void transmitString(char * str)
{
	uint16_t i;
	
	strcat(str, "\r");								// Добавляем символ конца строки
	
	for (i = 0; i < strlen(str); ++i)
	{
		USART2->DR = str[i];						// Передаём байт данных
		while ((USART2->SR & USART_SR_TC) == 0)
			;										// Ждём окончания передачи
	}
}

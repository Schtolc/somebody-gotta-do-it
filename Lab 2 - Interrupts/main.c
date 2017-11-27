#include "stm32f10x.h" 

#define DELAY_CYCLES 500000

void setNumber(uint32_t i);
void initOutputPorts(void);
void initButton(void);
void initTimer(void);
void delay(uint32_t cycles);

uint32_t current_number = 0;

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

	GPIOA->CRL = 0;
	GPIOA->CRL |= GPIO_CRL_MODE0_1;
	GPIOA->CRL |= GPIO_CRL_MODE1_1;
	GPIOA->CRL |= GPIO_CRL_MODE2_1;
	GPIOA->CRL |= GPIO_CRL_MODE3_1;
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

	setNumber(current_number);

	current_number++;
	if (current_number == 10)
		current_number = 0;
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

int main(void)
{
	initOutputPorts();
	initButton();
	initTimer();
	
	while(true)
	{
	}
}

void delay(uint32_t cycles)
{
    uint32_t i;
    for (i = 0; i < cycles; i++)
        ;
}

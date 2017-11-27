#include "stm32f10x.h"  

#define DELAY_CYCLES 500000

typedef enum Action {OFF = 0, ON = 1} Action;

void delay(uint32_t cycles);
void led_control(uint8_t led_number, Action action);

int ledon = 0;

int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;	// включить тактирование GPIOC
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	// включить тактирование GPIOC

	GPIOC->CRH = 0;											// очистка регистров конфигурации GPIOC
	GPIOC->CRH |= GPIO_CRH_MODE8_1;			// LD4, выход 2МГц
	GPIOC->CRH |= GPIO_CRH_MODE9_1;			// LD3, выход 2МГц
	
	GPIOC->CRL = 0;
	GPIOC->CRL |= GPIO_CRL_CNF0_1;
	
	while(1)
	{
		if (GPIOA->IDR & GPIO_IDR_IDR0)
		{
			if (ledon)
			{
				led_control(1, ON);
				led_control(2, OFF);
			}
			else
			{ 
				led_control(1, OFF);
				led_control(2, ON);
			}
			ledon = !ledon;
	  }
		delay(DELAY_CYCLES);
	}
}

void delay(uint32_t cycles)
{
	uint32_t i;
	for (i = 0; i < cycles; i++)
		;
}

void led_control(uint8_t led_number, Action action)
{
	switch (led_number)
	{
		case 1:
			GPIOC->BSRR |= (action == ON ? GPIO_BSRR_BS9 : GPIO_BSRR_BR9);
			break;
		case 2:
			GPIOC->BSRR |= (action == ON ? GPIO_BSRR_BS8 : GPIO_BSRR_BR8);
			break;
		default:
			break;
	}
}

#include "stm32f10x.h"  

#define DELAY_CYCLES 500000

typedef enum Action {OFF = 0, ON = 1} Action;

void delay(uint32_t cycles);
void led_control(uint8_t led_number, Action action);

int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;	// включить тактирование GPIOC

	GPIOC->CRH = 0;											// очистка регистров конфигурации GPIOC
	GPIOC->CRH |= GPIO_CRH_MODE8_1;			// LD4, выход 2МГц
	GPIOC->CRH |= GPIO_CRH_MODE9_1;			// LD3, выход 2МГц

	while(1)
	{
		led_control(3, ON);
		delay(DELAY_CYCLES);
		led_control(3, OFF);
		led_control(4, ON);
		delay(DELAY_CYCLES);
		led_control(4, OFF);
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
		case 3:
			GPIOC->BSRR |= (action == ON ? GPIO_BSRR_BS9 : GPIO_BSRR_BR9);
			break;
		case 4:
			GPIOC->BSRR |= (action == ON ? GPIO_BSRR_BS8 : GPIO_BSRR_BR8);
			break;
		default:
			break;
	}
}

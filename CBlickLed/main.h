#ifndef __MAIN_H
#define	__MAIN_H

#include "stm32f10x.h"  

// Величина задержки между вкл/выкл светодиодов
#define DELAY_VAL	500000

/* Управление светодиодами */

#define	LED3_ON()	GPIOC->BSRR |= GPIO_BSRR_BS9
#define	LED3_OFF()	GPIOC->BSRR |= GPIO_BSRR_BR9

#define	LED4_ON()	GPIOC->BSRR |= GPIO_BSRR_BS8
#define	LED4_OFF()	GPIOC->BSRR |= GPIO_BSRR_BR8

/* Прототипы функций */
void delay(uint32_t cycles);

#endif

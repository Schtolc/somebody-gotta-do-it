#ifndef __MAIN_H
#define	__MAIN_H

#include "stm32f10x.h" 
#include "stdbool.h"
#include "string.h"

// Раскомментировать #define,
// если нужно использовать DMA при передаче по USART
//#define USE_DMA

/* Размеры буферов приёма и передачи */


/* Управление светодиодами */
#define	LED1_ON()	GPIOD->BSRR |= GPIO_BSRR_BS7
#define	LED1_OFF()	GPIOD->BSRR |= GPIO_BSRR_BR7

#define	LED2_ON()	GPIOC->BSRR |= GPIO_BSRR_BS8
#define	LED2_OFF()	GPIOC->BSRR |= GPIO_BSRR_BR8

#define	LED3_ON()	GPIOD->BSRR |= GPIO_BSRR_BS3
#define	LED3_OFF()	GPIOD->BSRR |= GPIO_BSRR_BR3

#define	LED4_ON()	GPIOD->BSRR |= GPIO_BSRR_BS4
#define	LED4_OFF()	GPIOD->BSRR |= GPIO_BSRR_BR4

/* Прототипы функций */
void initPorts(void);
void initUART2(void);
void txStr(char *str);
void txStrWithDMA(char *str);
void delay(uint32_t takts);
void initButton(void);
void initTIM6(void);
void setNumber(uint32_t i);
#endif

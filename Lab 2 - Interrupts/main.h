#ifndef __MAIN_H
#define	__MAIN_H

#include "stm32f10x.h" 
#include "stdbool.h"

#define DELAY_VAL		1000000

/* Прототипы функций */
void initPorts(void);
void initButton(void);
void initTIM6(void);
void delay(uint32_t takts);
void setNumber(uint32_t i);

#endif

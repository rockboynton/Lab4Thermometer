/*
 * gpio.h
 *
 *  Created on: Dec 9, 2018
 *      Author: livingston
 */

#ifndef GPIO_H_
#define GPIO_H_

/**
 * How to use:
 *   In the C file you wish to use gpio port do the following:
 *   	0. include gpio.h header
 *
 *   		#include "gpio.h"
 *
 *   	1. Create a gpio pointer to the structure.
 *   					(usually as a file static pointer)
 *
 *   		EG: static volatile GPIO* GPIOC = 0x40020800;
 *
 *   	2. To use the control registers use the '->' operator
 *
 *   		EG:  GPIOC->MODER |= .......;
 *
 *   				or
 *
 *   		 	(*GPIOC).MODER (I like the above form).
 */

#include <inttypes.h>

#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define GPIOAEN 0		// GPIOA Enable is bit 0 in RCC_APB1LPENR
//Which bit enables GPIOC?
#define GPIOCEN 2


typedef struct {
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDER;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
} GPIO;

#endif /* GPIO_H_ */

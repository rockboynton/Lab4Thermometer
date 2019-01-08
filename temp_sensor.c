/*
 * temp_sensor.c
 *
 *  Created on: Jan 7, 2019
 *      Author: Rock Boynton
 * 
 * Implements functions specified in temp_sensor.h to use the MSOE dev board temperature sensor
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "temp_sensor.h"
#include "delay.h"
#include "gpio.h"

#define ADC1_CR2 (ADC1_BASE + ADC_CR2)
#define ADC1_SQR3 (ADC1_BASE + ADC_SQR3)

static volatile GPIO* GPIOB = 0x40020400;


void temp_init() {
    // Enable GPIOB in RCC_AHB1ENR
	*(RCC_AHB1ENR) |= (1 << GPIOBEN);

    // Enable ADC1EN in RCC_APB2ENR
	*(RCC_APB2ENR) |= (1 << ADC1EN);

    // Configure GPIOB pin 0 to input mode
    GPIOB->MODER = (GPIOB->MODER & ~0x00000003) | 0x00000000;

    // Turn on ADC1
    *(ADC1_CR2) |= 1; // ? ADON

    // Select channel ADC Channel 8 
    // One channel scan
    // n = ((n & ~(0xF << 16)) | 0b0110 << 16));
    *(ADC1_SQR3) = ((*(ADC1_SQR3) & ~0x1F) | 0x08);
}

uint16_t temp_current_fahrenheit() {
    // Start conversion 
    
}
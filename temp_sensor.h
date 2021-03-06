/*
 * temp_sensor.h 
 * 
 * API for interfacing with the MSOE dev board temperature sensor
 */

//Include Guards 
#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#define ADC1_BASE (volatile uint32_t*) 0x40012000
#define ADC_SR 0x00
#define ADC_CR2 0x08
#define ADC_SQR3 0x34
#define ADC_DR 0x4C

/**
 * Initialize the temperature sensor GPIO port.
 */
void temp_init();

/**
 * Displays the current temperature in fahrenheit.
 */
uint16_t temp_current_fahrenheit();

/**
 * Displays the current temperature in celsius.
 */
uint16_t temp_current_celsius();

/**
 * Displays the current warmest temperature in fahrenheit.
 */
uint16_t temp_max_fahrenheit();

/**
 * Displays the current coldest temperature in fahrenheit.
 */
uint16_t temp_min_fahrenheit();

/**
 * Displays the current warmest temperature in celsius.
 */
uint16_t temp_max_celsius();

/**
 * Displays the current coldest temperature in celsius.
 */
uint16_t temp_min_celsius();

uint16_t temp_voltage(); 

#endif
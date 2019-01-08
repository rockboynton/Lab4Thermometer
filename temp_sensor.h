/*
 * temp_sensor.h 
 * 
 * API for interfacing with the MSOE dev board temperature sensor
 */

//Include Guards 
#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

/**
 * Initialize the temperature sensor GPIO port.
 */
void temp_init();

void temp_current_fahrenheit();

void temp_current_celsius();

void temp_max_fahrenheit();

void temp_min_fahrenheit();

void temp_max_celsius();

void temp_min_celsius();

void temp_voltage(); 

#endif
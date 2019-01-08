/*
 * main.c
 *
 * Thermometer application using the temperature sensor on the CE Development Board.
 * 
 * C program to implement a simple thermometer using the Keypad and LCD.
 * 	YThermometer should  meet the following requirements:
 * 		1. Contains a clear intro/help screen outlining the basic API.
 * 		2. A current temperature mode which displays the current temperature.
 * 		3. Uses the LEDs to create a bar that shows the approximate current temperature (No lights  *         60F, All lights 80F)
 * 		4. An extremes mode which displays the current warmest and coldest temperatures read.
 * 		5. A trouble shooting screen that displays the current temperature and the input voltage    *          value coming from the temperatures sensor.
 *      Pressing a key on the keypad should toggle between Celsius and Fahrenheit. 
 */
#include <stdio.h>
#include <stdlib.h>
#include "uart_driver.h"
#include "led.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"

#define F_CPU 16000000UL

// 0 = main program
// 1 = Thermometer tests

#define DEBUG 0

// Initialize variables to be used 
uint8_t fahrenheit = 1; // 0 for Fahrenheit, 1 for Celsius
uint8_t key;

// File scope helper methods
void print_help_screen();
void display_temp_bar();
void current_temp_mode();
void extremes_mode();
void troubleshooting_mode();
void toggle_units();

// main
int main() {
	
	// Initialize hardware
	init_usart2(19200,F_CPU);
	led_init();
	lcd_init();
	key_init();
	temp_sensor_init();

	// --------------------- THERMOMETER TEST CODE -------------------
	if (DEBUG == 1) {
		while (1) {
			currentTemp = temp_sensor_getTemp;
			lcd_print_num(currentTemp);
			delay_1ms(1000);
			lcd_clear();
		}
	}
	//-----------------------------------------------------------

	// Main program 
	// Never return
	print_help_screen();
	lcd_home();
	while (1) {
		lcd_clear();
		led_allOff();

		display_temp_bar();

		key = key_getChar();
		switch (key) {
			case 'A':
				current_temp_mode();
				break;
			case 'B':
				extremes_mode();
				break;
			case 'C':
				troubleshooting_mode();
				break;
			case 'D':
				toggle_units();
				break;
			case '1':
				print_help_screen();
				break;	
			default:
				break;
		}
	// Never returns
	return 0;
}

void print_help_screen() {
	printf("A: Current Temperature Mode - displays the current temperature\n"
           "B: Extremes Mode - displays the current warmest and coldest temperatures read\n"
           "C: Trouble Shooting Mode - displays the current temperature and the input voltage value\n"
           "   coming from the temperatures sensor\n"
           "D: Toggle Celsius/Fahrenheit\n"
		   "1: Help Screen\n");
}

void display_temp_bar() {
	// 60 = 0 LEDs, 80 = 10 LEDs
	int temp = temp_current_fahrenheit() - 60; 
	for (int i = 0; i < temp; i += 2) {
		led_on(i);
	}
}

void current_temp_mode() {
	uint16_t currentTemp;
	lcd_print_string("Current Temp: ");
	if (fahrenheit) {
		currentTemp = temp_current_fahrenheit();
	} else {
		currentTemp = temp_current_celsius();
	}
	lcd_print_num(currentTemp);
}

void extremes_mode() { 
	uint16_t maxTemp;
	uint16_t minTemp;
	if (fahrenheit) {
		maxTemp = temp_max_fahrenheit();
		minTemp = temp_min_fahrenheit();
	} else {
		maxTemp = temp_max_celsius();
		minTemp = temp_min_celsius();
	}
	lcd_print_string("Max Temp: ");
	lcd_print_num(maxTemp);
	lcd_set_position(1, 0);
	lcd_print_string("Min Temp: ");
	lcd_print_num(minTemp);
}

void troubleshooting_mode() {
	current_temp_mode();
	lcd_set_position(1, 0);
	lcd_print_string("Input voltage value: ");
	lcd_print_num(temp_voltage());
} 

void toggle_units() {
	if (fahrenheit) {
		fahrenheit = 0;
	} else {
		fahrenheit = 1;
	}
}

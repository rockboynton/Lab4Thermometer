/*
 * main.c
 *
 *  Program to implement a basic 4 function calculator on the MSOE dev board LCD display
 * 	The display takes the form:  [_ op _ = __]  where each "_" is a single decimal digit and the op *  can be +, -, x, or /.
 *  - A, B, C, and D keys on the keypad are be used to specify addition, 
 *  subtraction, multiplication and division respectively.  
 *  - # performs a calculation and * moves the cursor to the first operand and 
 *  clears result.
 *  - Digits are specified from left to right jumping back and forth between the two 
 *  possible numbers to be operated on.
 *  Division results are rounded to the integer. 
 *  Prints an error message to the LCD upon a division by zero.

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
// 1 = keypad tests
// 2 = LCD tests
#define DEBUG 0

// Initialize variables to be used 
static char TEMPLATE[] = "1 + 1 = __";
uint8_t numChars;
static const uint8_t A_INDEX = 0;
static const uint8_t OP_INDEX = 2;
static const uint8_t B_INDEX = 4;
static const uint8_t RES_INDEX = 8;
static const uint8_t KEY_MAP[] = {
	0,1,2,3,4,5,6,7,8,9,
	'+','-','x','/','*','#',0 // Key A->+, Key B-> -, Key C->x, Key D->/
	};

// Operands
uint8_t a = 1;
uint8_t b = 1;

// Operator
uint8_t op = '+';

// Result
int res;

// Result string
uint8_t result[2];

// Valid flag
uint8_t valid;

// Current key
uint8_t key;

// Helper Functions
static int calculate(uint8_t a, uint8_t op, uint8_t b);
static void clear_res();
static void enter();


// main
int main(){
	
	// Initialize hardware
	init_usart2(19200,F_CPU);
	led_init();
	lcd_init();
	key_init();

	// --------------------- KEYPAD TEST CODE -------------------
	if (DEBUG == 2) {
		while (1) {
			key = KEY_MAP[key_getKey()];
			lcd_write_data(key);
		}
	}
	//-----------------------------------------------------------

	// --------------------- LCD TEST CODE ----------------------
	if (DEBUG == 1) {
		delay_1ms(1000);
		numChars = lcd_print_string(TEMPLATE);
			delay_1ms(1000);
		lcd_home();
			delay_1ms(1000);
		lcd_print_num(9);
			delay_1ms(1000);
		lcd_set_position(0,OP_INDEX);
			delay_1ms(1000);
		lcd_write_data('-');
			delay_1ms(1000);
		lcd_set_position(0,B_INDEX);
			delay_1ms(1000);
		lcd_print_num(5);
			delay_1ms(1000);
		lcd_set_position(0,RES_INDEX);
				delay_1ms(1000);
		sprintf(result, "%d", 4);
		lcd_print_string(result);
			delay_1ms(1000);
		while(1){}
	}
	// -------------------------------------------------------------

	// Main program 
	// Never return
	lcd_print_string(TEMPLATE);
	while (1) {
		lcd_set_position(0, A_INDEX);
		// get valid input for operand a, or clear result/enter
		valid = 0;
		while (!valid) {
			key = KEY_MAP[key_getKey()];
			if (key < 10 || key == '*' || key == '#') {
				valid = 1;
			}
		}
		// key is valid
		if (key == '*') { 
			clear_res();
			continue;
		} else if (key == '#') {
			enter();
			continue;
		} else {
			a = key;
			clear_res();
			lcd_set_position(0, A_INDEX);
			lcd_print_num(a);
		}

		lcd_set_position(0, OP_INDEX);
		// get valid input for operator, or clear result/enter
		valid = 0;
		while (!valid) {
			key = KEY_MAP[key_getKey()];
			if (key == '+' || key == '-' || key == 'x' || key == '/' || key == '*' || key == '#') {
				valid = 1;
			}
		}
		// key is valid
		if (key == '*') { 
			clear_res();
			continue;
		} else if (key == '#') {
			enter();
			continue;
		} else {
			op = key;
			clear_res();
			lcd_set_position(0, OP_INDEX);
			lcd_write_data(op);
		}

		lcd_set_position(0, B_INDEX);
		// get valid input for operand b, or clear result/enter
		valid = 0;
		while (!valid) {
			key = KEY_MAP[key_getKey()];
			if (key < 10 || key == '*' || key == '#') {
				valid = 1;
			}
		}
		// key is valid
		if (key == '*') { 
			clear_res();
			continue;
		} else if (key == '#') {
			enter();
			continue;
		} else {
			b = key;
			clear_res();
			lcd_set_position(0, B_INDEX);
			lcd_print_num(b);
		}
	}
	// Never returns
	return 0;
}

// File scope helper methods
static int calculate(uint8_t a, uint8_t op, uint8_t b) {
	int res = 0;
	switch (op) {
		case '+':
			res = a + b;
			break;
		case '-':
			res = a - b;
			break;
		case 'x':
			res = a * b;
			break;
		case '/':
			if (b == 0) {
				lcd_clear();
				lcd_print_string("Undef. Press any");
				lcd_set_position(1, 0);
				lcd_print_string("key to continue");
				key_getKey();
				lcd_clear();
				lcd_print_string(TEMPLATE);
			} else {
				res = a / b;
			}
			break;
		default:
			printf("invalid Operation.\n");
			break;
	}
	return res;
}

static void clear_res() {
	lcd_set_position(0, RES_INDEX);
	lcd_print_string("__");
	lcd_home();
}

static void enter() {
	lcd_set_position(0, RES_INDEX);
	lcd_print_string("  ");
	lcd_set_position(0, RES_INDEX);
	res = calculate(a, op, b);
	if (!(op == '/' && b == 0)) {
		sprintf(result, "%d", res);
		lcd_print_string(result);
	} 
}

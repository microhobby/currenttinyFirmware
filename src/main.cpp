/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * Current Mini
 * Main - setup - loop
 *
 * (C) Copyright 2018
 * Matheus Castello <matheus@castello.eng.br>
 */

#include <Arduino.h>
#include <board_core.h>
#include <console.h>
#include <plotter.h>

#include "command.h"

void setup() 
{
	/* Board specific initialization */
	board_setup();
	/* set data */
	currentSensor.vout_pin = CONFIG_CURRENT_MINI_VIN_PIN;
}

void loop() 
{	
	/* console */
	/*acs714_pololu_read_avg(&currentSensor, 64);
	console_clear_screen();
	console_print_double(currentSensor.vout, 3);
	console_print_double(currentSensor.current, 3);
	delay(100);*/

	/* check for commands */
	if (check_command()) {
		prepare_command();
	}

	execute_command();
	delay(10);
}

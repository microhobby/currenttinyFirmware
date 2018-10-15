/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * Current Tiny
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
	currentSensor.vout_pin = CONFIG_CURRENT_TINY_VIN_PIN;
}

void loop() 
{

	/* check for commands */
	if (check_command()) {
		prepare_command();
	}

	execute_command();
	delay(10);
}

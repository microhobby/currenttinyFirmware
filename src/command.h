/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * Current Tiny
 * Commands implementations
 *
 * (C) Copyright 2018
 * Matheus Castello <matheus@castello.eng.br>
 */

#include <Arduino.h>
#include <board_core.h>
#include <console.h>

#ifndef COMMANDS
#define COMMANDS

#define FUNCS_SIZE	3

/* data */
acs714_pololu_data currentSensor; 
String last_command;
String temp_command;
int last_command_id = -1;
typedef void (*function_callback)(void);
typedef struct {
	function_callback func;
	const char * name;
} funcs;

/* utils */
bool check_command();
void execute_command();

/* commands */
void flush_command();
void instant_command();
void version_command();
void stop_command();

/* declare commands */
funcs fxs[] = {
	{
		.func = &flush_command, 
		.name = "AT+FLUSH"
	},
	{
		.func = &instant_command,
		.name = "AT+INSTANT"
	},
	{
		.func = &version_command,
		.name = "AT+VERSION"
	},
	{
		.func = &stop_command,
		.name = "AT+STOP"
	}
};

function_callback search_func(const char * name)
{
	for (int i = 0; i < FUNCS_SIZE; i++) {
		if (!strcmp(name, fxs[i].name)) {
			last_command_id = i;
			return fxs[i].func;
		}
	}

	return NULL;
}

bool check_command()
{
	if (BoardSerial.available()) {
		temp_command = BoardSerial.readStringUntil('\n');
		temp_command.toUpperCase();

		BoardSerial.flush();

		if (temp_command.indexOf("AT+") != -1) {
			last_command = temp_command;
			return true;
		}
	}

	return false;
}

void prepare_command()
{
	search_func(last_command.c_str());
}

void execute_command()
{
	if (last_command_id >= 0)
		fxs[last_command_id].func();
}

/* implement here cause platformIO is trash config for compiler */
void flush_command()
{
	acs714_pololu_read_avg(&currentSensor, 10);
	console_print_double(currentSensor.current, 5);
}

void instant_command()
{
	acs714_pololu_read_avg(&currentSensor, 64);
	console_print_double(currentSensor.current, 5);
	last_command_id = -1;
}

void version_command()
{
	BoardSerial.println(CONFIG_FIRMWARE_VERSION);
	last_command_id = -1;
}

void stop_command()
{
	BoardSerial.println(0);
	last_command_id = -1;
}

#endif
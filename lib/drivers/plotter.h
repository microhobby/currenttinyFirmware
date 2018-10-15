/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * Plotter utils
 *
 * (C) Copyright 2018
 * Matheus Castello <matheus@castello.eng.br>
 */

#include <defconfig.h>
#include <Arduino.h>
#include <console.h>

#ifdef CONFIG_PLOTTER
#ifndef PLOTTER_CONFIG_H_
#define PLOTTER_CONFIG_H_

void plotter_write_data_max_min(float low_offset, float up_offset, float data)
{
	BoardSerial.print(low_offset);
	BoardSerial.print(" ");
	BoardSerial.print(up_offset);
	BoardSerial.print(" ");
	BoardSerial.println(data);
}

void plotter_write_data(double data)
{
	console_print_double(data, 3);
	BoardSerial.println();
}

#endif
#endif
/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * ACS712 Hall low current sensor Driver Header
 *
 * (C) Copyright 2018
 * Matheus Castello <matheus@castello.eng.br>
 */

#include <defconfig.h>
#include <Arduino.h>

#ifdef CONFIG_ACS712_SPARKFUN
#ifndef ACS712_CONFIG_H_
#define ACS712_CONFIG_H_

typedef struct {
	byte vout_pin;
	float vout;
	float current;
} acs712_sparkfun_data;

void acs712_sparkfun_read_avg(acs712_sparkfun_data *, int);

#endif
#endif
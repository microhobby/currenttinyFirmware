/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * ACS714 Pololu Hall low current sensor Driver Header
 *
 * (C) Copyright 2018
 * Matheus Castello <matheus@castello.eng.br>
 */

#include <defconfig.h>
#include <Arduino.h>

#ifdef CONFIG_ACS714_POLOLU
#ifndef ACS714_CONFIG_H_
#define ACS714_CONFIG_H_

typedef struct {
	byte vout_pin;
	double vout;
	double current;
} acs714_pololu_data;

void acs714_pololu_read_avg(acs714_pololu_data *, unsigned int);

#endif
#endif
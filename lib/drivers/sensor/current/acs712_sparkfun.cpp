/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * ACS712 Hall low current sensor Driver
 *
 * (C) Copyright 2018
 * Matheus Castello <matheus@castello.eng.br>
 */

#include "acs712_sparkfun.h"

#ifdef CONFIG_ACS712_SPARKFUN

void acs712_sparkfun_read_avg(acs712_sparkfun_data* data, int avg)
{
	int i, avg_sum = 0;
	float vout, current;

	for (i = 0; i < avg; i++) {
		avg_sum += analogRead(data->vout_pin);
		/* wait 2 milliseconds to adc to settle */
		delay(2);
	}

	avg_sum = avg_sum / avg;
	vout = CONFIG_ACS712_VADC * avg_sum;
	current = ACS712_CALC_CURRENT(vout);

	/* record data */
	data->vout = vout;
	data->current = current;

	return;
}

#endif
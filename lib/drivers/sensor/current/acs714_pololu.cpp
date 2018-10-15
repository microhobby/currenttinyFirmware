/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * ACS714 Pololu Hall low current sensor Driver
 *
 * (C) Copyright 2018
 * Matheus Castello <matheus@castello.eng.br>
 */

#include "acs714_pololu.h"

#ifdef CONFIG_ACS714_POLOLU

long acs714_pololu_read_vin()
{
	long result;

	ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
	delay(2);
	ADCSRA |= _BV(ADSC);

	while (bit_is_set(ADCSRA,ADSC));

	result = ADCL;
	result |= ADCH<<8;
	result = 1126400L / result;

	return result;
}

void acs714_pololu_read_avg(acs714_pololu_data* data, unsigned int avg)
{
	unsigned int i;
	long vin = 0, avg_sum = 0;
	double vout, current = 0.0;

	vin = acs714_pololu_read_vin();

	for (i = 0; i < avg; i++) {
		/* read */
		avg_sum = analogRead(data->vout_pin);
		
		/* calc with offsets */
		/*current += (avg_sum - CONFIG_ACS714_OFFSET) * CONFIG_ACS714_SPAN;*/

		/* calc normal */
		vout = ((float)avg_sum / 1024.0) * (float)vin;
		current += (vout - ((float)vin/2)) / 185.0;
		//((185.0 * (float)vin) / 5000.0);
	}

	current = current / avg;
	/*vout = ACS714_CALC_SENSE_VOLTAGE(avg_sum, vin);*/

	data->vout = vout;
	data->current = current;

	return;
}

#endif
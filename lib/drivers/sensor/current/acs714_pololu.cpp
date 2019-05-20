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

#ifdef CONFIG_PINSCHER
	ADMUX = _BV(MUX3) | _BV(MUX2);
#else
	ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif
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
	unsigned int i, j;
	long vin = 0, read_sum = 0;
	double vout, current = 0.0, zeroCurrentVCC;

	vin = acs714_pololu_read_vin();

	for (i = 0; i < avg; i++) {
		for (j = 0; j < 5; j++) {
			read_sum += analogRead(data->vout_pin);
			/* wait 2 milliseconds to adc to settle */
			delay(2);
		}
		zeroCurrentVCC = vin / 2;
		vout = ((read_sum / 5) * vin) / 1024.0;
		current += (vout - zeroCurrentVCC) / CONFIG_ACS714_SENSE;
		read_sum = 0;
	}

	current = current / avg;

	data->vout = vout;
	data->current = current;

	return;
}

#endif
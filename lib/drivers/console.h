/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * Console utils
 *
 * (C) Copyright 2018
 * Matheus Castello <matheus@castello.eng.br>
 */

#include <defconfig.h>
#include <Arduino.h>

#ifdef CONFIG_CONSOLE
#ifndef CONSOLE_CONFIG_H_
#define CONSOLE_CONFIG_H_

void console_clear_screen () 
{
	BoardSerial.write(27);
	BoardSerial.print("[2J");
  	BoardSerial.write(27);
  	BoardSerial.print("[H");   
}

void console_print_double(double val, byte precision)
{
	BoardSerial.print (int(val));
	
	if(precision > 0) {
		BoardSerial.print(".");
		unsigned long frac, mult = 1, frac1;
		byte padding = precision -1;
		
		while(precision--) 
			mult *=10;
		
		if(val >= 0) 
			frac = (val - int(val)) * mult; 
		else 
			frac = (int(val) - val) * mult;
	
		frac1 = frac;
	
		while(frac1 /= 10) 
			padding--;
	
		while(padding--) 
			BoardSerial.print("0");
		
		BoardSerial.print(frac,DEC) ;
	}
	
	BoardSerial.println("");
}

#endif
#endif
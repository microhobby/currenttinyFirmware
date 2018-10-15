/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * Current Mini
 * Board Initiliazation and config
 *
 * (C) Copyright 2018
 * Matheus Castello <matheus@castello.eng.br>
 */

#ifdef CONFIG_BOARD_CURRENT_MINI

#include <defconfig.h>
#include <Arduino.h>
#ifdef CONFIG_PINSCHER
#include <SoftwareSerial.h>
#endif
#include <acs714_pololu.h>

#ifdef CONFIG_PINSCHER
SoftwareSerial BoardSerial(CONFIG_SERIAL_RX_PIN, CONFIG_SERIAL_TX_PIN);
#else
HardwareSerial BoardSerial = Serial;
#endif

void board_setup()
{
	/* pinconf and pinmux */
#ifndef CONFIG_PINSCHER
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
#endif
	pinMode(CONFIG_CURRENT_MINI_VIN_PIN, INPUT);

	/* config BoardSerial */
	BoardSerial.begin(CONFIG_BoardSerial_BAUD_RATE);
	BoardSerial.flush();
}

#endif
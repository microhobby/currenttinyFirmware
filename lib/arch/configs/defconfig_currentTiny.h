/* SPDX-License-Identifier: GPL-3.0+ */
/*
 * Current Tiny DefConfigs
 *
 * (C) Copyright 2018
 * Matheus Castello <matheus@castello.eng.br>
 */

/* modules */
#define CONFIG_CONSOLE
#define CONFIG_PLOTTER
#define CONFIG_AT_INTERFACE
#undef CONFIG_ACS712_SPARKFUN
#define CONFIG_ACS714_POLOLU

/* pins */
#define CONFIG_CURRENT_TINY_VIN_PIN			A2
#ifdef CONFIG_PINSCHER
#define CONFIG_SERIAL_RX_PIN				2
#define CONFIG_SERIAL_TX_PIN				1
#endif

/* utils */
#define CONFIG_FIRMWARE_VERSION				"2018.1.10"
#define CONFIG_BoardSerial_BAUD_RATE 			9600

#ifdef CONFIG_ACS712_SPARKFUN
#define CONFIG_ACS712_SENSE				0.2
#define CONFIG_ACS712_VREF				2500
#define CONFIG_ACS712_VADC				4.88

#define ACS712_CALC_CURRENT(voltage) \
	((voltage - CONFIG_ACS712_VREF) * CONFIG_ACS712_SENSE)

#endif

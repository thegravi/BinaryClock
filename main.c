/*
 * main.c
 *
 *  Created on: 2014 rugp. 25
 *      Author: Gražvidas
 */

#include <avr/io.h>
#include "Drivers/UART/uart.h"
#include "Modules/Configuration/config.h"
#include "Modules/Protocol/protocol.h"

int main (void)
{
	UART_init(PROTO_receivedData);

	DDRC |= 1<<PC5;
	sei();

	UART_log("$ ");
//	uint8_t val;
//	CONFIG_setParam(CONFIG_PARAM_TIME_FORMAT, 1);
//	CONFIG_getParam(CONFIG_PARAM_TIME_FORMAT, &val);
//	UART_log("val: %d\n", val);
	while (1)
	{

	}

	return 0;
}

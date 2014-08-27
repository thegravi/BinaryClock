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
	UART_registerReceiveCallback(PROTO_receivedData);
	UART_init();
	CONFIG_init();

	UART_log("$ ");

	while (1)
	{

	}

	return 0;
}

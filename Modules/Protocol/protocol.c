/*
 * protocol.c
 *
 *  Created on: 2014 rugp. 25
 *      Author: Gravidas
 */

#include "protocol.h"

int8_t PROTO_parseData(char* buffer)
{
	char *pBuffer = buffer;

	if (memcmp(buffer, "binc", 4) != 0)
		return -1;

	pBuffer += 4;

	if (*pBuffer != _SPACE)
		return -1;

	pBuffer++;

	char argv[4][10];
	uint8_t argc = 0;
	uint8_t idx = 0;

	while (*pBuffer != '\0')
	{
		if (*pBuffer != _SPACE && *pBuffer != '-') {
			argv[argc][idx++] = *pBuffer++;
			continue;
		}
		else if (*pBuffer == _SPACE){
			argc++;
			idx = 0;
		}

		pBuffer++;
	}
	argc++;

	PROTO_processCommand(argc, argv);

	return 0;
}

int8_t PROTO_processCommand(uint8_t argc, char argv[][10])
{
//	UART_log("len: %d, %s %s\n", argc, argv[0], argv[1]);

	if (memcmp((void*)argv[0], (void*)"help", 4) == 0) {
		UART_log("Binary clock command list:\n");
		UART_log("-help\t\tLists all available commands\n");
		UART_log("-get\t\tReturs one of the parameters\n");
		UART_log("\ttime\tcurrent time\n");
		UART_log("\tbrightness\tLEDs intensity\n");
		UART_log("\ttimeformat\ttime format (24/12)\n");
		return 0;
	}

	if (memcmp((void*)argv[0], (void*)"get", 3) == 0) {

		if (memcmp((void*)argv[1], (void*)"timeformat", 10) == 0) {
			UART_log("Current time format: 24 h\n");
		}
		else if (memcmp((void*)argv[1], (void*)"brightness", 10) == 0) {
			UART_log("LEDs brightness: 73%\n");
		}
		else if (memcmp((void*)argv[1], (void*)"time", 4) == 0) {
			UART_log("Current Time: 23:41\n");
		}

		return 0;
	}

	return -1;
}

void PROTO_receivedData(char data)
{
	static char buffer[64];
	static uint8_t i = 0;

	if (data == _LF || data == _CR) {
		i = 0;
//		UART_log("\nReceived: %s\n", buffer);
		PROTO_parseData(buffer);
		memset((void*)buffer, 0, sizeof(buffer));
		UART_log("\n$ ");
		return;
	}

	if (data == _BS && i > 0) {
		buffer[--i] = 0;
		return;
	}

	if (i < 128 && data >= 32 && data < 127) {
		buffer[i++] = data;
		return;
	}
}

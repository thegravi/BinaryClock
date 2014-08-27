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
			uint8_t timeFormat;
			CONFIG_getParam(CONFIG_PARAM_TIME_FORMAT, &timeFormat);
			UART_log("Current time format: %s\n", (timeFormat == 12) ? "12" : "24");
		}
		else if (memcmp((void*)argv[1], (void*)"brightness", 10) == 0) {
			uint8_t brightness;
			CONFIG_getParam(CONFIG_PARAM_BRIGHTNESS, &brightness);
			UART_log("LEDs brightness: %d %\n", brightness);
		}
		else if (memcmp((void*)argv[1], (void*)"time", 4) == 0) {
			uint8_t hour;
			uint8_t minute;
			uint8_t second;
			CONFIG_getParam(CONFIG_PARAM_HOUR, &hour);
			CONFIG_getParam(CONFIG_PARAM_MINUTE, &minute);
			CONFIG_getParam(CONFIG_PARAM_SECOND, &second);
			UART_log("Current Time: %d:%d:%d\n", hour, minute, second);
		}

		return 0;
	}

	if (memcmp((void*)argv[0], (void*)"set", 3) == 0) {

		if (memcmp((void*)argv[1], (void*)"timeformat", 10) == 0) {
			uint8_t timeformat;
			if (memcmp((void*)argv[2], (void*)"12", 2) == 0) {
				timeformat = 12;
			}
			else if (memcmp((void*)argv[2], (void*)"24", 2) == 0) {
				timeformat = 24;
			}
			else {
				UART_log("-- Wrong time format: (12, 24)\n");
				return -1;
			}

			CONFIG_setParam(CONFIG_PARAM_TIME_FORMAT, timeformat);
		}

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

/*
 * protocol.h
 *
 *  Created on: 2014 rugp. 25
 *      Author: Gražvidas
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <string.h>
#include <stdint.h>

#include "../../Drivers/UART/uart.h"

int8_t PROTO_parseData(char* buffer);

int8_t PROTO_processCommand(uint8_t argc, char argv[][10]);

void PROTO_receivedData(char data);

#endif /* PROTOCOL_H_ */

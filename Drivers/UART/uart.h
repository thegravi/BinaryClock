/*
 * uart.h
 *
 *  Created on: 2013.11.23
 *      Author: Gražvidas
 */

#ifndef UART_H_
#define UART_H_

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#define LOG UART_log

#define _LF 0x0A
#define _CR 0x0D
#define _BS 0x08
#define _SPACE 0x20


void UART_init(void (*dataReceiveCallback)(char data));

void UART_log(char *format, ...);

#endif /* UART_H_ */

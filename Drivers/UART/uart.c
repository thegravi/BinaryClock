/*
 * uart.c
 *
 *  Created on: 2013.11.23
 *      Author: Gražvidas
 */

#include "uart.h"

static void (*dataReceiveCallback)(char);

void UART_init(void)
{
	// 38400 baud rate for a 8MHz Clock
	UCSRB  |= 1<<TXEN;
	UCSRC  |= 1<<UCSZ1 | 1<<UCSZ0;
	UBRRH   = 0;
	UBRRL   = 12;
	__asm__ __volatile__ ("sei");
}

void UART_registerReceiveCallback(void (*callback)(char))
{
	if (callback == NULL)
		return;

	dataReceiveCallback = callback;
	UCSRB |= 1<<RXCIE | 1<<RXEN;
}

static void UART_sendChar(char c)
{
	uint16_t timeout = 0xFFF;

	while (!(UCSRA & (1<<UDRE)) && timeout > 0)
		timeout--;

	UDR = c;
}

static void UART_sendString(const char* buffer, uint8_t len)
{
	while (len-- > 0)
		UART_sendChar(*buffer++);
}

static void UART_sendNumber(uint32_t byte, uint8_t base)
{
	const char hexChars[16] = "0123456789ABCDEF";
	char buff[20];
	memset(buff, 0, sizeof(buff));
	char *p;
	uint8_t len = 0;

	p = buff + sizeof(buff);

	do
	{
		*--p = hexChars[byte%base];
		byte /= base; len++;
	} while(byte > 0);

	UART_sendString(p, len);
}

void UART_log(char *format, ...)
{
	va_list args;
	va_start(args, format);

	uint8_t idx = 0;
	char buffer[65];
	memset(buffer, 0, sizeof(buffer));

	while (*format != '\0')
	{
		if (*format != '%')	{
			buffer[idx++] = *format++;
			continue;
		}

		if ((*format == '%') && (*format+1 == '%'))
		{
			buffer[idx++] = *format;
			format += 2;
			continue;
		}

		buffer[idx] = 0;
		UART_sendString(buffer, idx);
		idx = 0;
		format++;

		char *str;
		switch (*format)
		{
			case 'd':
				UART_sendNumber(va_arg(args, int), 10);
				break;

			case 'u':
				UART_sendNumber(va_arg(args, unsigned int), 10);
				break;

			case 'x':
				UART_sendNumber(va_arg(args, int), 16);
				break;

			case 'o':
				UART_sendNumber(va_arg(args, int), 8);
				break;

			case 'c':
				str = va_arg(args, char*);
				UART_sendChar(str);
				break;

			case 's':
				str = va_arg(args, char*);
				UART_sendString(str, strlen(str));
				break;

			default:
				// skip if data type is unknown
				buffer[idx++] = *format;
				break;
		}

		format++;

	}

	buffer[idx] = 0;
	UART_sendString(buffer, idx);
	idx = 0;

	va_end(args);
}

ISR (USART_RXC_vect)
{
	dataReceiveCallback(UDR);
}

/*
 * eeprom.c
 *
 *  Created on: 2014 rugp. 26
 *      Author: Gražvidas
 */

#include "eeprom.h"

int8_t EEPROM_writeByte(uint8_t addr, uint8_t value)
{
	eeprom_write_byte((uint8_t*) addr, value);
	return 0;
}

int8_t EEPROM_readByte(uint8_t addr, uint8_t *value)
{
	*value = eeprom_read_byte((uint8_t*) addr);
	return 0;
}

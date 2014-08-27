/*
 * eeprom.c
 *
 *  Created on: 2014 rugp. 26
 *      Author: Gražvidas
 */

#include "eeprom.h"

int8_t EEPROM_writeByte(uint8_t addr, uint8_t value)
{
	if (addr < _EEPROM_OFFSET_CONFIG ||
		addr >= (_EEPROM_OFFSET_CONFIG + CONFIG_PARAM_COUNT))
		return -1;

	eeprom_write_byte((uint8_t*) addr, value);
	return 0;
}

int8_t EEPROM_readByte(uint8_t addr, uint8_t *value)
{
	if (addr < _EEPROM_OFFSET_CONFIG ||
		addr >= (_EEPROM_OFFSET_CONFIG + CONFIG_PARAM_COUNT) ||
		((addr >= _EEPROM_OFFSET_DEF_CONFIG + CONFIG_PARAM_COUNT) &&
		 (addr < _EEPROM_OFFSET_DEF_CONFIG)))
		return -1;

	if (value == NULL)
		return -1;

	*value = eeprom_read_byte((uint8_t*) addr);
	return 0;
}

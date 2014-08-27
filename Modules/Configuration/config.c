/*
 * config.c
 *
 *  Created on: 2014 rugp. 25
 *      Author: Gražvidas
 */

#include "config.h"

static struct Config_t cfg[5];

// skipping 0x00 location for avr EEPROM reasons...
uint8_t EEMEM defaultConfig[CONFIG_PARAM_COUNT + 1] = {
		0,
		12,
		00,
		00,
		100,
		0
};

int8_t CONFIG_init(void)
{
	uint8_t value;
	EEPROM_readByte(_EEPROM_OFFSET_CONFIG, &value);

	if (value == 0xFF)
		goto _writeDefaultConfig;

	uint8_t id;
	for (id = _EEPROM_OFFSET_CONFIG; id < (CONFIG_PARAM_COUNT + _EEPROM_OFFSET_CONFIG); id++) {
		EEPROM_readByte(id, &value);

		if (value == 0xFF)
			goto _writeDefaultConfig;

		cfg[id].value = value;
	}

	return 0;

	_writeDefaultConfig:
	for (id = _EEPROM_OFFSET_CONFIG; id < (CONFIG_PARAM_COUNT + _EEPROM_OFFSET_CONFIG); id++) {
		EEPROM_readByte(_EEPROM_OFFSET_DEF_CONFIG + (id - _EEPROM_OFFSET_CONFIG), &value);
		EEPROM_writeByte(id, value);
		cfg[id - _EEPROM_OFFSET_CONFIG].value = value;
	}

	return 1;
}

int8_t CONFIG_setParam(uint8_t id, uint8_t value)
{
	if (id >= CONFIG_PARAM_COUNT)
		return -1;

	cfg[id].value = value;
	return EEPROM_writeByte(id, value);
}

int8_t CONFIG_getParam(uint8_t id, uint8_t* value)
{
	if (id >= CONFIG_PARAM_COUNT || value == NULL)
		return -1;

	*value = cfg[id].value;
	return 0;
}


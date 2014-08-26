/*
 * config.c
 *
 *  Created on: 2014 rugp. 25
 *      Author: Gražvidas
 */

#include "config.h"

static struct Config_t EEMEM cfg[] = {
		{23},
		{59},
		{54},
		{73},
		{0}
};

int8_t CONFIG_setParam(uint8_t id, uint8_t value)
{
	cfg[id].value = value;
	return EEPROM_writeByte(id, value);
}

int8_t CONFIG_getParam(uint8_t id, uint8_t* value)
{
	return EEPROM_readByte(id, value);
}


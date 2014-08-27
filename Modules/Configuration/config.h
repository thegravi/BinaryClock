/*
 * config.h
 *
 *  Created on: 2014 rugp. 25
 *      Author: Gražvidas
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>
#include "../../Drivers/EEPROM/eeprom.h"

#define _EEPROM_OFFSET_DEF_CONFIG 0x01
#define _EEPROM_OFFSET_CONFIG     0x08

enum {
	CONFIG_PARAM_HOUR = 0,
	CONFIG_PARAM_MINUTE,
	CONFIG_PARAM_SECOND,
	CONFIG_PARAM_BRIGHTNESS,
	CONFIG_PARAM_TIME_FORMAT,

	CONFIG_PARAM_COUNT
};

struct Config_t {
	uint8_t value;
};

/**
 * @brief Loads config from EEPROM
 * @return operation status
 */
int8_t CONFIG_init(void);

/**
 * @brief Sets configuration parameter
 * @param id - parameter id
 * @param value - parameter value
 * @return operation status
 */
int8_t CONFIG_setParam(uint8_t id, uint8_t value);

/**
 * @brief Gets configuration parameter
 * @param id - parameter id
 * @param value - pointer to value
 * @return operation status
 */
int8_t CONFIG_getParam(uint8_t id, uint8_t* value);

#endif /* CONFIG_H_ */

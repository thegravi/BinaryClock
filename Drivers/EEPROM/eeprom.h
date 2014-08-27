/*
 * eeprom.h
 *
 *  Created on: 2014 rugp. 26
 *      Author: Gražvidas
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>

#include <avr/eeprom.h>
#include "../../Modules/Configuration/config.h"

/**
 * @brief Writes 1 byte to EEPROM memory
 * @param addr - address of EEPROM memory byte
 * @param value - value to be written
 * @return operation status
 */
int8_t EEPROM_writeByte(uint8_t addr, uint8_t value);

/**
 * @brief Reads 1 byte from EEPROM memory
 * @param addr - address of EEPROM memory byte
 * @param value - pointer to value
 * @return operation status
 */
int8_t EEPROM_readByte(uint8_t addr, uint8_t *value);

#endif /* EEPROM_H_ */

/*
 * crc15.h
 *
 *  Created on: Mar. 31, 2025
 *      Author: arvin
 */

#ifndef INC_CRC15_H_
#define INC_CRC15_H_

// CRC15 implementation for the LTC6811
#include <stddef.h>
#include <stdint.h>

void crc15_init_table(void);

uint16_t crc15_calculate(uint8_t *data, size_t len);

#endif /* INC_CRC15_H_ */

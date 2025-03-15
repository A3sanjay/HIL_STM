/*
 * i2c_defs.h
 *
 *  Created on: Feb 26, 2025
 *      Author: arvin
 */

#ifndef INC_I2C_DEFS_H_
#define INC_I2C_DEFS_H_

#include <stdint.h>

typedef struct
{
	uint8_t register_value;
} PCA9555_Register_Map;

typedef struct
{
	uint16_t register_value;
} MAX17261_Register_Map;

#endif /* INC_I2C_DEFS_H_ */

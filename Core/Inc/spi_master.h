/*
 * spi_master.h
 *
 *  Created on: Mar. 18, 2025
 *      Author: arvin
 */

#ifndef INC_SPI_MASTER_H_
#define INC_SPI_MASTER_H_

#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "spi_slave.h"
#include "gpio_defs.h"

// TODO: Change this to 2 (STM32 F401RE only has 1 SPI port for DAC, but when we switch to G series, we can update this)
#define NUM_SPI_MASTER_PORTS 1

void spi_master_init(SPI_Settings *settings);
void spi_master_transmit_buffer(SPI_Settings *settings, SPI_Storage *storage);

#endif /* INC_SPI_MASTER_H_ */

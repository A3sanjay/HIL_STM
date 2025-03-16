/*
 * i2c_spi_periphs_control.h
 *
 *  Created on: Feb 27, 2025
 *      Author: arvin
 */

#ifndef INC_I2C_SPI_PERIPHS_CONTROL_H_
#define INC_I2C_SPI_PERIPHS_CONTROL_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    NO_BOARD,
    POWER_DISTRIBUTION,
    CENTRE_CONSOLE,
    MCI,
    BMS
} BOARDS_TO_SIMULATE;

void board_control_init();
void set_board(BOARDS_TO_SIMULATE board);

#endif /* INC_I2C_SPI_PERIPHS_CONTROL_H_ */

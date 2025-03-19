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

#include "main.h"
#include "i2c_slave.h"
#include "spi_slave.h"
#include "uart_control.h"

#define MAX_I2C_SLAVES_TO_SIMULATE NUM_I2C_PORTS
#define MAX_SPI_SLAVES_TO_SIMULATE NUM_SPI_PORTS

#define TASK_NOTIFICATION_INDEX 1

typedef struct
{
    TaskHandle_t *board_control_task;
} Board_Control;

typedef enum
{
    NO_BOARD,
    POWER_DISTRIBUTION,
    CENTRE_CONSOLE,
    MCI,
    BMS
} BOARDS_TO_SIMULATE;

void board_control_init(Board_Control *control);
void board_control_init_comms(void *params);
void board_control_start_simulation(BOARDS_TO_SIMULATE board);
void board_control_setup_complete(UART_Control *control);

#endif /* INC_I2C_SPI_PERIPHS_CONTROL_H_ */

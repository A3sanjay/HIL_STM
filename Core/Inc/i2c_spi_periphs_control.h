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
#define MAX_SPI_MASTERS NUM_SPI_MASTER_PORTS // DACs are the main peripheral that we need a master for

#define TASK_NOTIFICATION_INDEX 1

// TODO: Update for all simulation boards with reasonable defautl values from 0V - 4V (DAC range) for the signal that the board receives
#define NUM_POWER_DISTRIBUTION_ANALOG_SIGNALS 1
#define POWER_DISTRIBUTION_ANALOG_SIGNAL_DEFAULT_VOLTAGE 2.5F
#define CENTRE_CONSOLE_ANALOG_SIGNAL_DEFAULT_VOLTAGE 2.5F
#define MCI_ANALOG_SIGNAL_DEFAULT_VOLTAGE 2.5F
#define BMS_ANALOG_SIGNAL_DEFAULT_VOLTAGE 2.5F

typedef struct
{
    TaskHandle_t *board_control_task;
    UART_HandleTypeDef *huart;
} Board_Control;

typedef enum
{
    NO_BOARD,
    POWER_DISTRIBUTION,
    CENTRE_CONSOLE,
    MCI,
    BMS,
    NUM_VALID_BOARDS
} BOARDS_TO_SIMULATE;

void board_control_init(Board_Control *control);
void board_control_start_simulation(BOARDS_TO_SIMULATE board);
void board_control_setup_complete(UART_Control *control);

#endif /* INC_I2C_SPI_PERIPHS_CONTROL_H_ */

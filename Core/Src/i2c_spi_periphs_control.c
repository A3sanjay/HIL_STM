/*
 * i2c_spi_periphs_control.c
 *
 *  Created on: Feb 27, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "i2c_defs.h"
#include "i2c_slave.h"
#include "spi_slave.h"
#include "i2c_spi_periphs_control.h"
#include "pca9555.h"
#include "max17261.h"
#include "mcp2515.h"
#include "uart_control.h"
#include "proto_processing.h"
#include "set_board_response.pb.h"

// Necessary handle definitions for interfaces that we are using
extern I2C_HandleTypeDef hi2c1;
SPI_TypeDef *spi_handle2 = SPI2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;

// Static variables for peripherals, protocols, etc
static PCA9555_Settings pca9555_settings[MAX_I2C_SLAVES_TO_SIMULATE];
static PCA9555_Storage pca9555_storage[MAX_I2C_SLAVES_TO_SIMULATE];

static MAX17261_Settings max17261_settings[MAX_I2C_SLAVES_TO_SIMULATE];
static MAX17261_Storage max17261_storage[MAX_I2C_SLAVES_TO_SIMULATE];

static MCP2515_Settings mcp2515_settings[MAX_I2C_SLAVES_TO_SIMULATE];
static MCP2515_Storage mcp2515_storage[MAX_I2C_SLAVES_TO_SIMULATE];

static I2C_Settings i2c_settings[MAX_I2C_SLAVES_TO_SIMULATE];
static SPI_Settings spi_settings[MAX_SPI_SLAVES_TO_SIMULATE];

void board_control_init(Board_Control *control)
{
    xTaskCreate(board_control_init_comms, "Board Simulation Init Task", NORMAL_STACK_DEPTH, (void *)control, NORMAL_PRIORITY, control->board_control_task);
}

void board_control_init_comms(void *params)
{
    Board_Control *control = (Board_Control *)params;

    // Run UART setup loop and wait for task notification indicating that the reception is complete
    UART_Settings uart_settings;
    UART_Control uart_control = {.huart = &huart1, .uart_settings = &uart_settings, .uart_rx_cp_notify_task = control->board_control_task};
    uart_control_rx_init(&uart_control, board_control_setup_complete);
    uart_control_rx_start(&uart_control);

    ulTaskNotifyTakeIndexed(TASK_NOTIFICATION_INDEX, pdTRUE, BLOCK_INDEFINITELY);

    InitializeBoard board;
    Proto_Decode_Storage storage = {.buffer_to_decode = uart_control.raw_data, .buffer_to_decode_length = uart_control.data_length, .decoded_output = (void *)&board};
    proto_process_decode_board_init(&storage);

    board_control_start_simulation(board.board_to_run);
}

void board_control_start_simulation(BOARDS_TO_SIMULATE board)
{
    if (board == POWER_DISTRIBUTION)
    {
        // Power Distribution has 2 x GPIO Expanders
        pca9555_init_reg_map();

        // Initialize the first GPIO Expander
        i2c_settings[0].hi2c = &hi2c1;
        i2c_settings[0].i2c_slave_address = PCA9555_I2C_ADDRESS;
        i2c_settings[0].i2c_slave_id = I2C_PORT_1;
        pca9555_settings[0].i2c_settings = &i2c_settings[0];
        pca9555_init(&pca9555_settings[0], &pca9555_storage[0]);

        // Initialize the second GPIO Expander
        i2c_settings[1].hi2c = &hi2c1;
        i2c_settings[1].i2c_slave_address = PCA9555_I2C_ADDRESS;
        i2c_settings[1].i2c_slave_id = I2C_PORT_2;
        pca9555_settings[1].i2c_settings = &i2c_settings[1];
        pca9555_init(&pca9555_settings[1], &pca9555_storage[1]);
    }
    else if (board == CENTRE_CONSOLE)
    {
        // Centre Console has 2 x GPIO Expanders
        pca9555_init_reg_map();

        // Initialize the first GPIO Expander
        i2c_settings[0].hi2c = &hi2c1;
        i2c_settings[0].i2c_slave_address = PCA9555_I2C_ADDRESS;
        i2c_settings[0].i2c_slave_id = I2C_PORT_1;
        pca9555_settings[0].i2c_settings = &i2c_settings[0];
        pca9555_init(&pca9555_settings[0], &pca9555_storage[0]);

        // Initialize the second GPIO Expander
        i2c_settings[1].hi2c = &hi2c1;
        i2c_settings[1].i2c_slave_address = PCA9555_I2C_ADDRESS;
        i2c_settings[1].i2c_slave_id = I2C_PORT_2;
        pca9555_settings[1].i2c_settings = &i2c_settings[1];
        pca9555_init(&pca9555_settings[1], &pca9555_storage[1]);
    }
    else if (board == MCI)
    {
        // MCI has 1 x SPI -> CAN converter
        mcp2515_init_reg_map();

        // Initialize SPI -> CAN converter
        spi_settings[0].spi_handle = spi_handle2;
        spi_settings[0].spi_port = SPI_PORT_2;
        spi_settings[0].timer_handle = &htim3;
        mcp2515_settings[0].spi_settings = &spi_settings[0];
        mcp2515_init(&mcp2515_settings[0], &mcp2515_storage[0]);
    }
    else if (board == BMS)
    {
        // BMS has 1 x Current Sense + 1 x AFE
        max17261_init_reg_map();

        // Initialize the Current Sense
        i2c_settings[0].hi2c = &hi2c1;
        i2c_settings[0].i2c_slave_address = MAX17261_I2C_ADDRESS;
        i2c_settings[0].i2c_slave_id = I2C_PORT_1;
        max17261_settings[0].i2c_settings = &i2c_settings[0];
        max17261_init(&max17261_settings[0], &max17261_storage[0]);
    }
}

void board_control_setup_complete(UART_Control *control)
{
    // Sends the data to the queue
    vTaskNotifyGiveIndexedFromISR(*(control->uart_rx_cp_notify_task), TASK_NOTIFICATION_INDEX, NULL);
}

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
#include "ltc6811.h"
#include "mcp4811.h"
#include "uart_control.h"
#include "proto_processing.h"
#include "set_board_response.pb.h"

// Necessary handle definitions for interfaces that we are using
extern I2C_HandleTypeDef hi2c1;
SPI_TypeDef *spi_handle2 = SPI2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;

// Static variables for peripherals, protocols, etc
static PCA9555_Settings pca9555_settings[MAX_NUM_PCA9555];
static PCA9555_Storage pca9555_storage[MAX_NUM_PCA9555];

static MAX17261_Settings max17261_settings[MAX_NUM_MAX17261];
static MAX17261_Storage max17261_storage[MAX_NUM_MAX17261];

static MCP2515_Settings mcp2515_settings[MAX_NUM_MCP2515];
static MCP2515_Storage mcp2515_storage[MAX_NUM_MCP2515];

static LTC6811_Settings ltc6811_settings[MAX_NUM_LTC6811];
static LTC6811_Storage ltc6811_storage[MAX_NUM_LTC6811];

static I2C_Settings i2c_settings[MAX_I2C_SLAVES_TO_SIMULATE];
static SPI_Settings spi_settings[MAX_SPI_SLAVES_TO_SIMULATE];

static UART_Control uart_control;

void board_control_init(Board_Control *control)
{
    xTaskCreate(board_control_init_comms, "Board Simulation Init Task", NORMAL_STACK_DEPTH, (void *)control, NORMAL_PRIORITY, control->board_control_task);
}

void board_control_init_comms(void *params)
{
    Board_Control *control = (Board_Control *)params;

    // Run UART setup loop and wait for task notification indicating that the reception is complete
    UART_Settings uart_settings;
    uart_control.huart = control->huart;
    uart_control.uart_settings = &uart_settings;
    uart_control.uart_rx_cp_notify_task = control->board_control_task;
    uart_control_rx_init(&uart_control, board_control_setup_complete);
    uart_control_rx_start(&uart_control);

    ulTaskNotifyTake(TRUE, BLOCK_INDEFINITELY);

    InitializeBoard board;
    Proto_Decode_Storage storage = {.buffer_to_decode = uart_control.raw_data, .buffer_to_decode_length = uart_control.data_length, .decoded_output = (void *)&board};
    proto_process_decode_board_init(&storage);

    // Verify validity of input, send acknowledgement message back to RPi and start simulation of chosen board
    BOARDS_TO_SIMULATE board_to_run = board.board_to_run;
    if (NO_BOARD < board_to_run < NUM_VALID_BOARDS)
    {
        uint8_t buffer_to_encode[MIN_BOARD_RESPONSE_BUFFER_SIZE];
        Board_Response response = {.acknowledgement = BOARD_RESPONSE_MESSAGE_RECEIVED};
        Proto_Encode_Storage storage = {.buffer_to_encode = buffer_to_encode, .buffer_to_encode_length = sizeof(buffer_to_encode)};
        proto_process_encode_board_response(&response, &storage);

        uart_control_tx_add_end_line(buffer_to_encode, storage.encoded_buffer_length);
        uart_settings.tx_data = buffer_to_encode;
        uart_settings.bytes_to_send = storage.encoded_buffer_length + 1;
        uart_control_tx(&uart_settings);

        board_control_start_simulation(board.board_to_run);
    }
}

void board_control_start_simulation(BOARDS_TO_SIMULATE board)
{
    if (board == POWER_DISTRIBUTION)
    {
        // Power Distribution has 2 x GPIO Expanders + 1 x Analog Signal
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

        // Init one DAC on SPI3 and set voltage output to PD default
        GPIO_Pin mcp4811_cs_pin = {.gpio_port = SPI3_CS_GPIO_Port, .gpio_pin = SPI3_CS_Pin};
        SPI_Settings mcp4811_spi_settings = {.spi_handle = SPI3, .spi_port = SPI_PORT_3, .cs_pin = &mcp4811_cs_pin};
        MCP4811_Settings mcp4811_settings = {.spi_settings = &mcp4811_spi_settings};
        MCP4811_Storage mcp4811_storage;
        mcp4811_init(&mcp4811_settings, &mcp4811_storage);
        float voltage_to_set = POWER_DISTRIBUTION_ANALOG_SIGNAL_DEFAULT_VOLTAGE;
        mcp4811_set_voltage(&mcp4811_settings, &mcp4811_storage, voltage_to_set);
    }
    else if (board == CENTRE_CONSOLE)
    {
        // Centre Console has 2 x GPIO Expanders + 2 x Analog Signal
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
        // MCI has 1 x SPI -> CAN converter + 1 x Analog Signal

        // Initialize SPI -> CAN converter
        spi_settings[0].spi_handle = spi_handle2;
        spi_settings[0].spi_port = SPI_PORT_2;
        spi_settings[0].timer_handle = &htim3;
        mcp2515_settings[0].spi_settings = &spi_settings[0];
        mcp2515_init(&mcp2515_settings[0], &mcp2515_storage[0]);
    }
    else if (board == BMS)
    {
        // BMS has 1 x Current Sense + 1 x AFE + 2 x Analog Signal
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
    // Updates data and sends a task notification to activate main HIL simulation (consider using a queue)
    memcpy(uart_control.raw_data, control->raw_data, control->data_length);
    uart_control.data_length = control->data_length;
    vTaskNotifyGiveFromISR(*(control->uart_rx_cp_notify_task), NULL);
}

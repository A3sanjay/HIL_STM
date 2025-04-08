/*
 * ltc6811.h
 *
 *  Created on: Mar 30, 2025
 *      Author: arvin
 */

#ifndef INC_LTC6811_H_
#define INC_LTC6811_H_

#include <stdint.h>

#include "ltc6811_defs.h"
#include "spi_defs.h"
#include "spi_slave.h"

#define MAX_NUM_LTC6811 1

#define LTC6811_SPI_RX_BUFFER_SIZE 10
#define LTC6811_SPI_TX_BUFFER_SIZE 50

// This is the number of devices we are using (max of 12 devices can be daisy-chained together)
#define LTC6811_NUM_DEVICES 3

#define LTC6811_SPI_PORT SPI_PORT_1

#define LTC6811_PEC_LENGTH 2

#define LTC6811_VOLTAGE_LENGTH 6
#define LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH LTC6811_VOLTAGE_LENGTH + LTC6811_PEC_LENGTH

#define LTC6811_VOLTAGE_DEFAULT_VAL_HIGH_BYTE 0x98
#define LTC6811_VOLTAGE_DEFAULT_VAL_LOW_BYTE 0xF8

#define LTC6811_TEMP_LENGTH 6
#define LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH LTC6811_TEMP_LENGTH + LTC6811_PEC_LENGTH

#define LTC6811_TEMP_DEFAULT_VAL_HIGH_BYTE 0x61
#define LTC6811_TEMP_DEFAULT_VAL_LOW_BYTE 0xA8

// Important byte indexes to start processing data
#define LTC6811_COMMAND_BYTE_END_INDEX 2
#define LTC6811_PEC_END_INDEX 4

typedef struct
{
    SPI_Settings *spi_settings;
} LTC6811_Settings;

typedef struct
{
    uint8_t rx_data[LTC6811_SPI_RX_BUFFER_SIZE];
    uint8_t tx_data[LTC6811_SPI_TX_BUFFER_SIZE];
    LTC6811_Register_Map ltc6811_reg_map[LTC6811_NUM_DEVICES][LTC6811_NUM_GROUPS];
} LTC6811_Storage;

void ltc6811_init(LTC6811_Settings *settings, LTC6811_Storage *storage);
void ltc6811_process_byte(SPI_Settings *settings);
void ltc6811_process_received_data(SPI_Settings *settings);

#endif /* INC_LTC6811_H_ */

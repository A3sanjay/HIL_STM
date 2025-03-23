/*
 * mcp4811.h
 *
 *  Created on: Mar. 18, 2025
 *      Author: arvin
 */

#ifndef SRC_MCP4811_H_
#define SRC_MCP4811_H_

#include <stdint.h>
#include <stdbool.h>

#include "spi_defs.h"
#include "spi_master.h"
#include "spi_slave.h"
#include "gpio_defs.h"

#define MAX_NUM_MCP4811 10

#define MCP4811_SPI_RX_BUFFER_SIZE 10
#define MCP4811_SPI_TX_BUFFER_SIZE 10

#define MCP4811_SPI_PORT SPI_PORT_3

#define INPUT_DATA_BYTES_START_BIT_POS 2
#define SHDN_BIT_POS 12
#define GA_BIT_POS 13
#define EN_MSG_BIT_POS 15

#define NUM_DATA_BITS 10 // MCP4811 is the 10-bit variant

#define GAIN_1X_BIT_VAL 1
#define GAIN_2X_BIT_VAL 0

#define SHDN_DEVICE_ACTIVE_BIT_VAL 1
#define SHDN_DEVICE_OFF_BIT_VAL 0

#define EN_MSG_TRUE 0
#define EN_MSG_FALSE 1 // Pretty pointless to use this (DAC will ignore voltage set command)

#define V_REF 2.048f
// TODO: Verify that this is correct
#define DAC_PRECISION 10

#define MAX_OUTPUT_VOLTAGE (2 * V_REF)

typedef struct
{
    SPI_Settings *spi_settings;
    GPIO_Pin *cs_pin;
} MCP4811_Settings;

typedef struct
{
    uint8_t rx_data[MCP4811_SPI_RX_BUFFER_SIZE];
    uint8_t tx_data[MCP4811_SPI_TX_BUFFER_SIZE];
} MCP4811_Storage;

void mcp4811_init(MCP4811_Settings *settings, MCP4811_Storage *storage);
void mcp4811_set_voltage(MCP4811_Settings *settings, MCP4811_Storage *storage, float voltage);
void mcp4811_shutdown_dac(MCP4811_Settings *settings, MCP4811_Storage *storage);

#endif /* SRC_MCP4811_H_ */

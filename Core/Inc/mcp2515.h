/*
 * mcp2515.h
 *
 *  Created on: Mar 5, 2025
 *      Author: arvin
 */

#ifndef SRC_MCP2515_H_
#define SRC_MCP2515_H_

#include <stdint.h>

#include "mcp2515_defs.h"
#include "spi_slave.h"

#define MAX_NUM_MCP2515 1

#define MCP2515_SPI_RX_BUFFER_SIZE 10
#define MCP2515_SPI_TX_BUFFER_SIZE 10

#define MCP2515_SPI_PORT SPI_PORT_2

#define MCP2515_COMMAND_BYTE_END_INDEX 1

typedef struct
{
    SPI_Settings *spi_settings;
    SPI_Storage *spi_storage;
} MCP2515_Settings;

typedef struct
{
    uint8_t rx_data[MCP2515_SPI_RX_BUFFER_SIZE];
    uint8_t tx_data[MCP2515_SPI_TX_BUFFER_SIZE];
    MCP2515_Register_Map mcp2515_reg_map[MCP2515_NUM_REGISTERS];
    uint8_t mcp2515_num_registers;
} MCP2515_Storage;

void mcp2515_init(MCP2515_Settings *settings, MCP2515_Storage *storage);
void mcp2515_process_byte(SPI_Settings *settings, SPI_Storage *storage);
void mcp2515_process_received_data(SPI_Settings *settings, SPI_Storage *storage);

#endif /* SRC_MCP2515_H_ */

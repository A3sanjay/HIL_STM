/*
 * spi_defs.h
 *
 *  Created on: Mar 1, 2025
 *      Author: arvin
 */

#ifndef INC_SPI_DEFS_H_
#define INC_SPI_DEFS_H_

#include <stdint.h>
#include <stdbool.h>

#include "main.h"

typedef struct
{
	uint8_t register_value;
} MCP2515_Register_Map;

typedef enum
{
	SPI_PORT_1,
	SPI_PORT_2,
	SPI_PORT_3,
	SPI_PORT_4,
	NUM_SPI_PORTS
} SPI_PORTS;

typedef struct
{
	SPI_TypeDef *spi_handle;
	SPI_PORTS spi_port;
	TIM_HandleTypeDef *timer_handle;
	uint8_t *rx_data;
	uint8_t rx_index;
	uint8_t rx_buffer_size;
	bool rx_byte_callback;
	uint8_t *tx_data;
	uint8_t tx_index;
	uint8_t bytes_to_send;
	uint8_t tx_buffer_size;
	// TODO: Move to MCPStorage struct
	MCP2515_Register_Map *mcp2515_reg_map;
	uint8_t mcp2515_num_registers;
} SPI_Settings;

#endif /* INC_SPI_DEFS_H_ */

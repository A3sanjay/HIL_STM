/*
 * spi_slave.h
 *
 *  Created on: Feb 28, 2025
 *      Author: arvin
 */

#ifndef INC_SPI_SLAVE_H_
#define INC_SPI_SLAVE_H_

#include "main.h"
#include "spi_defs.h"
#include "spi_slave_fsm_defs.h"

#include <stdbool.h>

typedef enum
{
    SPI_PORT_1,
    SPI_PORT_2,
    NUM_SPI_PORTS
} SPI_PORTS;

typedef struct
{
    SPI_SLAVE_FSM_STATES spi_slave_state;
    SPI_SLAVE_SELECT spi_slave_select;
} SPI_FSM;

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

void spi_init(SPI_Settings *settings, SPI_SLAVE_SELECT slave_select, void (*spi_rx_process_cb)(SPI_Settings *), void (*spi_byte_process_cb)(SPI_Settings *));

#endif /* INC_SPI_SLAVE_H_ */

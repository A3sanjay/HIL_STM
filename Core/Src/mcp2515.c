/*
 * mcp2515.c
 *
 *  Created on: Mar 5, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "spi_slave.h"
#include "mcp2515.h"

static MCP2515_Register_Map initial_mcp2515_reg_map[MCP2515_NUM_REGISTERS] = {0};

void mcp2515_init_reg_map()
{
    for (uint8_t i = 0; i < MCP2515_NUM_REGISTERS; i++)
    {
        if (i == MCP2515_CTRL_REG_CANSTAT)
        {
            initial_mcp2515_reg_map[i].register_value = MCP2515_CTRL_REG_CANSTAT_VAL;
        }
        else if (i == MCP2515_CTRL_REG_CANCTRL)
        {
            initial_mcp2515_reg_map[i].register_value = MCP2515_CTRL_REG_CANCTRL_VAL;
        }
        else if (i == MCP2515_CTRL_REG_CNF2)
        {
            initial_mcp2515_reg_map[i].register_value = MCP2515_CTRL_REG_CNF2_VAL;
        }
        else if (i == MCP2515_CTRL_REG_CNF3)
        {
            initial_mcp2515_reg_map[i].register_value = MCP2515_CTRL_REG_CNF3_VAL;
        }
        else
        {
            initial_mcp2515_reg_map[i].register_value = MCP2515_REG_DEFAULT_VAL;
        }
    }
}

// TODO: Revisit the structure of what goes in SPI layer and what goes in device driver layer
void mcp2515_init(MCP2515_Settings *settings, MCP2515_Storage *storage)
{
    memcpy(storage->mcp2515_reg_map, initial_mcp2515_reg_map, sizeof(initial_mcp2515_reg_map));

    settings->spi_settings->rx_data = storage->rx_data;
    settings->spi_settings->rx_index = 0;
    settings->spi_settings->rx_buffer_size = MCP2515_SPI_RX_BUFFER_SIZE;
    settings->spi_settings->tx_data = storage->tx_data;
    settings->spi_settings->tx_index = 0;
    settings->spi_settings->tx_buffer_size = MCP2515_SPI_TX_BUFFER_SIZE;
    settings->spi_settings->mcp2515_reg_map = storage->mcp2515_reg_map;
    settings->spi_settings->mcp2515_num_registers = MCP2515_NUM_REGISTERS;

    // TODO: Create a callbacks struct for the device callbacks instead of passing in one by one
    spi_slave_init(settings->spi_settings, MCP2515, mcp2515_process_received_data, mcp2515_process_byte);
}

void mcp2515_process_byte(SPI_Settings *settings)
{
    uint8_t command_byte = settings->rx_data[0];
    // Handle read instructions
    switch (command_byte)
    {
    case MCP2515_CMD_READ:
        if (settings->rx_index == 1)
        {
            // Just command byte received
            settings->rx_byte_callback = true;
        }
        else if (settings->rx_index == 2)
        {
            // Argument has been received
            uint8_t argument = settings->rx_data[1];
            // TODO: Fill tx buffer with max register values starting from argument, and keep sending until CS pin goes HIGH
            // TODO: Check what's wrong with multi-byte response
            // for (uint8_t i = 0; i < settings->tx_buffer_size; i++)
            // {
            //     settings->tx_data[i] = settings->mcp2515_reg_map[argument + i].register_value;
            // }
            settings->tx_index = 0;
            settings->bytes_to_send = 10;
            settings->rx_byte_callback = false;
            LL_SPI_EnableIT_TXE(settings->spi_handle);
        }
        break;
    case MCP2515_CMD_READ_STATUS:
        // Fill tx buffer with status value
        settings->tx_data[0] = settings->mcp2515_reg_map[MCP2515_CMD_READ_STATUS].register_value;
        settings->tx_index = 0;
        settings->bytes_to_send = 1;
        LL_SPI_EnableIT_TXE(settings->spi_handle);
        break;
    case MCP2515_CMD_READ_RX_RXB0SIDH:
        // TODO: Fill tx buffer with sample CAN messages to send back
        break;
    case MCP2515_CMD_READ_RX_RXB1SIDH:
        // TODO: Fill tx buffer with sample CAN messages to send back
        break;
    }
}

void mcp2515_process_received_data(SPI_Settings *settings)
{
    // Handle write instructions
    uint8_t command_byte = settings->rx_data[0];
    uint8_t num_bytes_received = settings->rx_index;
    uint8_t reg;
    switch (command_byte)
    {
    case MCP2515_CMD_RESET:
        // TODO: Reset all registers
        break;
    case MCP2515_CMD_WRITE:;
        reg = settings->rx_data[1];
        for (uint8_t i = 0; i < num_bytes_received - 2; i++)
        {
            settings->mcp2515_reg_map[reg + i].register_value = settings->rx_data[i + 2];
        }
        break;
    case MCP2515_CMD_LOAD_TX_TXB0SIDH:
        // TODO: Add the reg map updates and rest of the cases for LOAD_TX (similar to CMD_RTS)
        break;
    case MCP2515_CMD_RTS_TXB0:
        // Set 3rd bit of CTRL registers
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB0CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB1:
        // Set 3rd bit of CTRL registers
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB1CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB2:
        // Set 3rd bit of CTRL registers
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB2CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB0_TXB1:
        // Set 3rd bit of CTRL registers
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB0CTRL].register_value |= 0b100;
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB1CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB0_TXB2:
        // Set 3rd bit of CTRL registers
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB0CTRL].register_value |= 0b100;
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB2CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB1_TXB2:
        // Set 3rd bit of CTRL registers
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB1CTRL].register_value |= 0b100;
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB2CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB0_TXB1_TXB2:
        // Set 3rd bit of CTRL registers
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB0CTRL].register_value |= 0b100;
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB1CTRL].register_value |= 0b100;
        settings->mcp2515_reg_map[MCP2515_CTRL_REG_TXB2CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_BIT_MODIFY:;
        // Modify bits in specified register
        reg = settings->rx_data[1];
        uint8_t mask = settings->rx_data[2];
        uint8_t data = settings->rx_data[3];
        uint8_t val_to_write = (data & mask) | (settings->mcp2515_reg_map[reg].register_value & ~mask);
        settings->mcp2515_reg_map[reg].register_value = val_to_write;
        break;
    }
}

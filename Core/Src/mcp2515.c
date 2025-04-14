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

// Only one MCP2515 will ever exist on our system
static MCP2515_Settings mcp2515_settings;
static MCP2515_Storage mcp2515_storage;

static void mcp2515_init_reg_map(MCP2515_Storage *storage)
{
    // Initialize reg_map during init to default values
    memset(storage->mcp2515_reg_map, 0, sizeof(storage->mcp2515_reg_map));

    for (uint8_t i = 0; i < storage->mcp2515_num_registers; i++)
    {
        if (i == MCP2515_CTRL_REG_CANSTAT)
        {
            storage->mcp2515_reg_map[i].register_value = MCP2515_CTRL_REG_CANSTAT_VAL;
        }
        else if (i == MCP2515_CTRL_REG_CANCTRL)
        {
            storage->mcp2515_reg_map[i].register_value = MCP2515_CTRL_REG_CANCTRL_VAL;
        }
        else if (i == MCP2515_CTRL_REG_CNF2)
        {
            storage->mcp2515_reg_map[i].register_value = MCP2515_CTRL_REG_CNF2_VAL;
        }
        else if (i == MCP2515_CTRL_REG_CNF3)
        {
            storage->mcp2515_reg_map[i].register_value = MCP2515_CTRL_REG_CNF3_VAL;
        }
        else
        {
            storage->mcp2515_reg_map[i].register_value = MCP2515_REG_DEFAULT_VAL;
        }
    }
}

void mcp2515_init(MCP2515_Settings *settings, MCP2515_Storage *storage)
{
    mcp2515_init_reg_map(storage);

    settings->spi_storage->rx_data = storage->rx_data;
    settings->spi_storage->rx_index = 0;
    settings->spi_storage->rx_buffer_size = MCP2515_SPI_RX_BUFFER_SIZE;
    settings->spi_storage->tx_data = storage->tx_data;
    settings->spi_storage->tx_index = 0;
    settings->spi_storage->tx_buffer_size = MCP2515_SPI_TX_BUFFER_SIZE;
    storage->mcp2515_num_registers = MCP2515_NUM_REGISTERS;

    SPI_Callbacks spi_callbacks = {.spi_byte_process_cb = mcp2515_process_byte, .spi_rx_process_cb = mcp2515_process_received_data};

    spi_slave_init(settings->spi_settings, settings->spi_storage, MCP2515, &spi_callbacks);

    memcpy(&mcp2515_settings, settings, sizeof(MCP2515_Settings));
    memcpy(&mcp2515_storage, storage, sizeof(MCP2515_Storage));
}

void mcp2515_process_byte(SPI_Settings *settings, SPI_Storage *storage)
{
    // Exit early if this byte does not need to be processed
    if (storage->rx_index != MCP2515_COMMAND_BYTE_END_INDEX && !settings->rx_byte_callback)
    {
        return;
    }

    uint8_t command_byte = storage->rx_data[0];

    // Handle read instructions
    switch (command_byte)
    {
    case MCP2515_CMD_READ:
        if (storage->rx_index == 1)
        {
            // Just command byte received
            settings->rx_byte_callback = true;
        }
        else if (storage->rx_index == 2)
        {
            // Argument has been received
            uint8_t argument = storage->rx_data[1];
            // TODO: Fill tx buffer with max register values starting from argument, and keep sending until CS pin goes HIGH
            // for (uint8_t i = 0; i < storage->tx_buffer_size; i++)
            // {
            //     storage->tx_data[i] = mcp2515_storage.mcp2515_reg_map[argument + i].register_value;
            // }
            storage->tx_index = 0;
            storage->bytes_to_send = 10;
            settings->rx_byte_callback = false;
            LL_SPI_EnableIT_TXE(settings->spi_handle);
        }
        break;
    case MCP2515_CMD_READ_STATUS:
        // Fill tx buffer with status value
        storage->tx_data[0] = mcp2515_storage.mcp2515_reg_map[MCP2515_CMD_READ_STATUS].register_value;
        storage->tx_index = 0;
        storage->bytes_to_send = 1;
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

void mcp2515_process_received_data(SPI_Settings *settings, SPI_Storage *storage)
{
    // Handle write instructions
    uint8_t command_byte = storage->rx_data[0];
    uint8_t num_bytes_received = storage->rx_index;
    uint8_t reg;
    switch (command_byte)
    {
    case MCP2515_CMD_RESET:
        // TODO: Reset all registers
        break;
    case MCP2515_CMD_WRITE:;
        reg = storage->rx_data[1];
        for (uint8_t i = 0; i < num_bytes_received - 2; i++)
        {
            mcp2515_storage.mcp2515_reg_map[reg + i].register_value = storage->rx_data[i + 2];
        }
        break;
    case MCP2515_CMD_LOAD_TX_TXB0SIDH:
        // TODO: Add the reg map updates and rest of the cases for LOAD_TX (similar to CMD_RTS)
        break;
    case MCP2515_CMD_RTS_TXB0:
        // Set 3rd bit of CTRL registers
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB0CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB1:
        // Set 3rd bit of CTRL registers
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB1CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB2:
        // Set 3rd bit of CTRL registers
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB2CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB0_TXB1:
        // Set 3rd bit of CTRL registers
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB0CTRL].register_value |= 0b100;
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB1CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB0_TXB2:
        // Set 3rd bit of CTRL registers
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB0CTRL].register_value |= 0b100;
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB2CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB1_TXB2:
        // Set 3rd bit of CTRL registers
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB1CTRL].register_value |= 0b100;
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB2CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_RTS_TXB0_TXB1_TXB2:
        // Set 3rd bit of CTRL registers
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB0CTRL].register_value |= 0b100;
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB1CTRL].register_value |= 0b100;
        mcp2515_storage.mcp2515_reg_map[MCP2515_CTRL_REG_TXB2CTRL].register_value |= 0b100;
        break;
    case MCP2515_CMD_BIT_MODIFY:;
        // Modify bits in specified register
        reg = storage->rx_data[1];
        uint8_t mask = storage->rx_data[2];
        uint8_t data = storage->rx_data[3];
        uint8_t val_to_write = (data & mask) | (mcp2515_storage.mcp2515_reg_map[reg].register_value & ~mask);
        mcp2515_storage.mcp2515_reg_map[reg].register_value = val_to_write;
        break;
    }
}

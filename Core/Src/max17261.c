/*
 * max17261.c
 *
 *  Created on: Mar 1, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "max17261.h"
#include "i2c_slave.h"

static MAX17261_Register_Map initial_max17261_reg_map[MAX17261_NUM_REGISTERS] = {0};

static MAX17261_Settings max17261_settings;
static MAX17261_Storage max17261_storage;

void max17261_init_reg_map()
{
    for (uint8_t i = 0; i < MAX17261_NUM_REGISTERS; i++)
    {
        if (i == MAX17261_STATUS)
        {
            initial_max17261_reg_map[i].register_value = MAX17261_STATUS_REG_DEFAULT_VAL;
        }
        else if (i == MAX17261_VCELL)
        {
            initial_max17261_reg_map[i].register_value = MAX17261_VCELL_REG_DEFAULT_VAL;
        }
        else if (i == MAX17261_CURRENT)
        {
            initial_max17261_reg_map[i].register_value = MAX17261_CURRENT_REG_DEFAULT_VAL;
        }
        else if (i == MAX17261_TEMP)
        {
            initial_max17261_reg_map[i].register_value = MAX17261_TEMP_REG_DEFAULT_VAL;
        }
        else
        {
            initial_max17261_reg_map[i].register_value = MAX17261_REG_DEFAULT_VAL;
        }
    }
}

void max17261_init(MAX17261_Settings *settings, MAX17261_Storage *storage)
{
    settings->i2c_settings->rx_data = storage->rx_data;
    settings->i2c_settings->rx_buffer_size = MAX17261_I2C_RX_BUFFER_SIZE;
    settings->i2c_settings->tx_data = storage->tx_data;
    settings->i2c_settings->tx_buffer_size = MAX17261_I2C_TX_BUFFER_SIZE;
    memcpy(storage->max17261_reg_map, &initial_max17261_reg_map, sizeof(initial_max17261_reg_map));
    settings->i2c_settings->max17261_reg_map = &(storage->max17261_reg_map);
    settings->i2c_settings->max17261_num_registers = MAX17261_NUM_REGISTERS;

    I2C_Callbacks i2c_callbacks = {.i2c_process_received_data = max17261_process_received_data, .i2c_process_address = max17261_process_address};
    i2c_init(settings->i2c_settings, MAX17261, &i2c_callbacks);
}

void max17261_process_received_data(I2C_Settings *settings, I2C_FSM *i2c_fsm)
{
    // Only one byte was received, so it was a write before read operation
    if (settings->hi2c->XferCount == settings->hi2c->XferSize - 1)
    {
        // Use the received register to pre-load the response
        uint8_t reg_to_read = settings->rx_data[0];
        uint16_t data = settings->max17261_reg_map[reg_to_read].register_value;
        settings->tx_data[0] = (uint8_t)(data & 0xFF);
        settings->tx_data[1] = (uint8_t)((data >> 8) & 0xFF);

        i2c_fsm->i2c_slave_state = MAX17261_SLAVE_RX;
    }
    // Handling a multi-byte write operation
    else if (settings->hi2c->XferCount == 0)
    {
        if (i2c_fsm->i2c_slave_state == MAX17261_SLAVE_RX)
        {
            // Write the value into the register map
            uint8_t reg_to_write = settings->rx_data[0];
            uint16_t data_to_write = ((uint16_t)settings->rx_data[2] << 8) | settings->rx_data[1];
            // Don't update MAX17261_MODEL_I_CFG
            if (reg_to_write != MAX17261_MODEL_I_CFG)
            {
                settings->max17261_reg_map[reg_to_write].register_value = data_to_write;
            }
        }

        i2c_fsm->i2c_slave_select = I2C_NO_SLAVE;
        i2c_fsm->i2c_slave_state = I2C_IDLE;
    }

    // memset(settings->rx_data, 0, settings->rx_buffer_size);

    HAL_I2C_EnableListen_IT(settings->hi2c);
}

void max17261_process_address(I2C_Settings *settings, I2C_FSM *i2c_fsm, I2C_Callback_Info *cb_info)
{
    uint8_t i2c_slave_address = cb_info->i2c_slave_address;
    uint8_t transfer_direction = cb_info->transfer_direction;

    if (transfer_direction == I2C_TX)
    {
        // Master is transmitting and slave needs to receive
        HAL_I2C_Slave_Seq_Receive_IT(settings->hi2c, settings->rx_data, MAX17261_I2C_NUM_BYTES_TO_RECEIVE, I2C_FIRST_FRAME);

        i2c_fsm->i2c_slave_select = MAX17261;
        i2c_fsm->i2c_slave_state = MAX17261_SLAVE_RX;
    }
    else if (transfer_direction == I2C_RX)
    {
        // Master is requesting data and slave needs to send
        HAL_I2C_Slave_Seq_Transmit_IT(settings->hi2c, settings->tx_data, MAX17261_I2C_NUM_BYTES_TO_SEND, I2C_FIRST_AND_LAST_FRAME);

        i2c_fsm->i2c_slave_state = MAX17261_SLAVE_TX;
    }
}

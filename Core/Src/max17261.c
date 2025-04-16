/*
 * max17261.c
 *
 *  Created on: Mar 1, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "max17261.h"
#include "i2c_slave.h"
#include "proto_processing.h"
#include "uart_control.h"
#include "update_event_message.pb.h"

extern UART_HandleTypeDef huart1;

static MAX17261_Settings max17261_settings;
static MAX17261_Storage max17261_storage;

// Send an I2C Write Update Event message for MAX17261 over UART and encode using Proto
static void prv_max17261_send_i2c_write_update_event(uint8_t register_to_update, uint16_t value_to_write)
{
    I2C_Write_Update_Event i2c_update_event = {.peripheral_to_update = MAX17261_I2C_WRITE_EVENT, .i2c_address = MAX17261_I2C_ADDRESS, .register_to_update = register_to_update, .value_to_write = value_to_write};

    uint8_t buffer_to_encode[MIN_I2C_WRITE_UPDATE_EVENT_BUFFER_SIZE];
    Proto_Encode_Storage storage = {.buffer_to_encode = buffer_to_encode, sizeof(buffer_to_encode)};
    proto_process_encode_i2c_write_update_event(&i2c_update_event, &storage);

    uart_control_tx_add_end_line(buffer_to_encode, storage.encoded_buffer_length);
    UART_Settings settings = {&huart1, .tx_data = buffer_to_encode, .bytes_to_send = storage.encoded_buffer_length};
    uart_control_tx(&settings);
}

static void max17261_init_reg_map(MAX17261_Register_Map *reg_map, uint8_t num_registers)
{
    for (uint8_t i = 0; i < num_registers; i++)
    {
        if (i == MAX17261_STATUS)
        {
            reg_map[i].register_value = MAX17261_STATUS_REG_DEFAULT_VAL;
        }
        else if (i == MAX17261_VCELL)
        {
            reg_map[i].register_value = MAX17261_VCELL_REG_DEFAULT_VAL;
        }
        else if (i == MAX17261_CURRENT)
        {
            reg_map[i].register_value = MAX17261_CURRENT_REG_DEFAULT_VAL;
        }
        else if (i == MAX17261_TEMP)
        {
            reg_map[i].register_value = MAX17261_TEMP_REG_DEFAULT_VAL;
        }
        else
        {
            reg_map[i].register_value = MAX17261_REG_DEFAULT_VAL;
        }
    }
}

void max17261_init(MAX17261_Settings *settings, MAX17261_Storage *storage)
{
    max17261_init_reg_map(storage->max17261_reg_map, MAX17261_NUM_REGISTERS);
    storage->max17261_num_registers = MAX17261_NUM_REGISTERS;

    settings->i2c_storage->rx_data = storage->rx_data;
    settings->i2c_storage->rx_buffer_size = MAX17261_I2C_RX_BUFFER_SIZE;
    settings->i2c_storage->tx_data = storage->tx_data;
    settings->i2c_storage->tx_buffer_size = MAX17261_I2C_TX_BUFFER_SIZE;

    I2C_Callbacks i2c_callbacks = {.i2c_process_received_data = max17261_process_received_data, .i2c_process_address = max17261_process_address};
    i2c_init(settings->i2c_settings, settings->i2c_storage, MAX17261, &i2c_callbacks);
}

void max17261_process_address(I2C_Settings *settings, I2C_Storage *storage, I2C_FSM *i2c_fsm, I2C_Callback_Info *cb_info)
{
    uint8_t i2c_slave_address = cb_info->i2c_slave_address;
    uint8_t transfer_direction = cb_info->transfer_direction;

    if (transfer_direction == I2C_TX)
    {
        // Master is transmitting and slave needs to receive
        HAL_I2C_Slave_Seq_Receive_IT(settings->hi2c, storage->rx_data, MAX17261_I2C_NUM_BYTES_TO_RECEIVE, I2C_FIRST_FRAME);

        i2c_fsm->i2c_slave_select = MAX17261;
        i2c_fsm->i2c_slave_state = MAX17261_SLAVE_RX;
    }
    else if (transfer_direction == I2C_RX)
    {
        // Master is requesting data and slave needs to send
        HAL_I2C_Slave_Seq_Transmit_IT(settings->hi2c, storage->tx_data, MAX17261_I2C_NUM_BYTES_TO_SEND, I2C_FIRST_AND_LAST_FRAME);

        i2c_fsm->i2c_slave_state = MAX17261_SLAVE_TX;
    }
}

void max17261_process_received_data(I2C_Settings *settings, I2C_Storage *storage, I2C_FSM *i2c_fsm)
{
    // Only one byte was received, so it was a write before read operation
    if (settings->hi2c->XferCount == settings->hi2c->XferSize - 1)
    {
        // Use the received register to pre-load the response
        uint8_t reg_to_read = storage->rx_data[0];
        uint16_t data = max17261_storage.max17261_reg_map[reg_to_read].register_value;
        storage->tx_data[0] = (uint8_t)(data & 0xFF);
        storage->tx_data[1] = (uint8_t)((data >> 8) & 0xFF);

        i2c_fsm->i2c_slave_state = MAX17261_SLAVE_RX;
    }
    // Handling a multi-byte write operation
    else if (settings->hi2c->XferCount == 0)
    {
        if (i2c_fsm->i2c_slave_state == MAX17261_SLAVE_RX)
        {
            // Write the value into the register map
            uint8_t reg_to_write = storage->rx_data[0];
            uint16_t data_to_write = ((uint16_t)storage->rx_data[2] << 8) | storage->rx_data[1];
            // Don't update MAX17261_MODEL_I_CFG
            if (reg_to_write != MAX17261_MODEL_I_CFG)
            {
                max17261_storage.max17261_reg_map[reg_to_write].register_value = data_to_write;
                prv_max17261_send_i2c_write_update_event(reg_to_write, data_to_write);
            }
        }

        i2c_fsm->i2c_slave_select = I2C_NO_SLAVE;
        i2c_fsm->i2c_slave_state = I2C_IDLE;
    }

    // memset(storage->rx_data, 0, storage->rx_buffer_size);

    HAL_I2C_EnableListen_IT(settings->hi2c);
}

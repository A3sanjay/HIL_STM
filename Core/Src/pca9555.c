/*
 * pca9555.c
 *
 *  Created on: Feb 21, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "pca9555.h"
#include "i2c_slave.h"
#include "proto_processing.h"
#include "uart_control.h"
#include "update_event_message.pb.h"

extern UART_HandleTypeDef huart1;

static PCA9555_Settings pca9555_settings;
static PCA9555_Storage pca9555_storage;

// Send an I2C Write Update Event message for PCA9555 over UART and encode using Proto
static void prv_pca9555_send_i2c_write_update_event(uint8_t register_to_update, uint8_t value_to_write)
{
    // Encode using Proto and send over UART
    I2C_Write_Update_Event i2c_update_event = {.peripheral_to_update = PCA9555_I2C_WRITE_EVENT, .i2c_address = PCA9555_I2C_ADDRESS, .register_to_update = register_to_update, .value_to_write = value_to_write};

    uint8_t buffer_to_encode[MIN_I2C_WRITE_UPDATE_EVENT_BUFFER_SIZE];
    Proto_Encode_Storage storage = {.buffer_to_encode = buffer_to_encode, sizeof(buffer_to_encode)};
    proto_process_encode_i2c_write_update_event(&i2c_update_event, &storage);

    uart_control_tx_add_end_line(buffer_to_encode, storage.encoded_buffer_length);
    UART_Settings settings = {&huart1, .tx_data = buffer_to_encode, .bytes_to_send = storage.encoded_buffer_length};
    uart_control_tx(&settings);
}

static void pca9555_init_reg_map(PCA9555_Register_Map *reg_map, uint8_t num_registers)
{
    for (uint8_t i = 0; i < num_registers; i++)
    {
        if (i == PCA9555_CONFIGURATION_0)
        {
            reg_map[i].register_value = PCA9555_CONFIGURATION_0_REG_DEFAULT_VAL;
        }
        else if (i == PCA9555_CONFIGURATION_1)
        {
            reg_map[i].register_value = PCA9555_CONFIGURATION_1_REG_DEFAULT_VAL;
        }
        else
        {
            reg_map[i].register_value = PCA9555_REG_DEFAULT_VAL;
        }
    }
}

void pca9555_init(PCA9555_Settings *settings, PCA9555_Storage *storage)
{
    pca9555_init_reg_map(storage->pca9555_reg_map, PCA9555_NUM_REGISTERS);
    storage->pca9555_num_registers = PCA9555_NUM_REGISTERS;

    settings->i2c_storage->rx_data = storage->rx_data;
    settings->i2c_storage->rx_buffer_size = PCA9555_I2C_RX_BUFFER_SIZE;
    settings->i2c_storage->tx_data = storage->tx_data;
    settings->i2c_storage->tx_buffer_size = PCA9555_I2C_TX_BUFFER_SIZE;

    I2C_Callbacks i2c_callbacks = {.i2c_process_received_data = pca9555_process_received_data, .i2c_process_address = pca9555_process_address};
    i2c_init(settings->i2c_settings, settings->i2c_storage, PCA9555, &i2c_callbacks);

    memcpy(&pca9555_settings, settings, sizeof(PCA9555_Settings));
    memcpy(&pca9555_storage, storage, sizeof(PCA9555_Storage));
}

void pca9555_process_address(I2C_Settings *settings, I2C_Storage *storage, I2C_FSM *i2c_fsm, I2C_Callback_Info *cb_info)
{
    uint8_t i2c_slave_address = cb_info->i2c_slave_address;
    uint8_t transfer_direction = cb_info->transfer_direction;

    if (transfer_direction == I2C_TX)
    {
        // Master is transmitting and slave needs to receive
        HAL_I2C_Slave_Seq_Receive_IT(settings->hi2c, storage->rx_data, PCA9555_I2C_NUM_BYTES_TO_RECEIVE, I2C_FIRST_FRAME);

        i2c_fsm->i2c_slave_select = PCA9555;
        i2c_fsm->i2c_slave_state = PCA9555_SLAVE_RX;
    }
    else if (transfer_direction == I2C_RX)
    {
        // Master is requesting data and slave needs to send
        HAL_I2C_Slave_Seq_Transmit_IT(settings->hi2c, storage->tx_data, PCA9555_I2C_NUM_BYTES_TO_SEND, I2C_FIRST_AND_LAST_FRAME);

        i2c_fsm->i2c_slave_state = PCA9555_SLAVE_TX;
    }
}

void pca9555_process_received_data(I2C_Settings *settings, I2C_Storage *storage, I2C_FSM *i2c_fsm)
{
    // Only one byte was received, so it was a write before read operation
    if (settings->hi2c->XferCount == settings->hi2c->XferSize - 1)
    {
        // Use the received register to pre-load the response
        uint8_t reg_to_read = storage->rx_data[0];
        storage->tx_data[0] = pca9555_storage.pca9555_reg_map[reg_to_read].register_value;

        i2c_fsm->i2c_slave_state = PCA9555_SLAVE_RX;
    }
    // Handling a multi-byte write operation
    else if (settings->hi2c->XferCount == 0)
    {
        if (i2c_fsm->i2c_slave_state == PCA9555_SLAVE_RX)
        {
            // Write the value into the register map
            uint8_t reg_to_write = storage->rx_data[0];
            uint8_t data_to_write = storage->rx_data[1];
            pca9555_storage.pca9555_reg_map[reg_to_write].register_value = data_to_write;
            // prv_pca9555_send_i2c_write_update_event(reg_to_write, data_to_write);
        }

        i2c_fsm->i2c_slave_select = I2C_NO_SLAVE;
        i2c_fsm->i2c_slave_state = I2C_IDLE;
    }

    // memset(storage->rx_data, 0, storage->rx_buffer_size);

    HAL_I2C_EnableListen_IT(settings->hi2c);
}

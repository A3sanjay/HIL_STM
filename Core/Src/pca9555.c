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

static PCA9555_Register_Map initial_pca9555_reg_map[PCA9555_NUM_REGISTERS] = {0};

// Send an I2C Write Update Event message for PCA9555 over UART and encode using Proto
static void prv_pca9555_send_i2c_write_update_event(uint8_t register_to_update, uint8_t value_to_write)
{
    // Encode using Proto and send over UART
    I2C_Write_Update_Event i2c_update_event = {.peripheral_to_update = PCA9555_I2C_WRITE_EVENT, .i2c_address = PCA9555_I2C_ADDRESS, .register_to_update = register_to_update, .value_to_write = value_to_write};

    uint8_t buffer_to_encode[MIN_I2C_WRITE_UPDATE_EVENT_BUFFER_SIZE];
    Proto_Encode_Storage storage = {.buffer_to_encode = buffer_to_encode, sizeof(buffer_to_encode)};
    proto_process_encode_i2c_write_update_event(&i2c_update_event, &storage);

    UART_Settings settings = {&huart1, .tx_data = buffer_to_encode, .bytes_to_send = storage.encoded_buffer_length};
    uart_control_tx(&settings);
}

void pca9555_init_reg_map()
{
    for (uint8_t i = 0; i < PCA9555_NUM_REGISTERS; i++)
    {
        if (i == PCA9555_CONFIGURATION_0)
        {
            initial_pca9555_reg_map[i].register_value = PCA9555_CONFIGURATION_0_REG_DEFAULT_VAL;
        }
        else if (i == PCA9555_CONFIGURATION_1)
        {
            initial_pca9555_reg_map[i].register_value = PCA9555_CONFIGURATION_1_REG_DEFAULT_VAL;
        }
        else
        {
            initial_pca9555_reg_map[i].register_value = PCA9555_REG_DEFAULT_VAL;
        }
    }
}

// TODO: Revisit the structure of what goes in I2C layer and what goes in device driver layer
void pca9555_init(PCA9555_Settings *settings, PCA9555_Storage *storage)
{
    memcpy(storage->pca9555_reg_map, &initial_pca9555_reg_map, sizeof(initial_pca9555_reg_map));

    settings->i2c_settings->rx_data = storage->rx_data;
    settings->i2c_settings->rx_buffer_size = PCA9555_I2C_RX_BUFFER_SIZE;
    settings->i2c_settings->tx_data = storage->tx_data;
    settings->i2c_settings->tx_buffer_size = PCA9555_I2C_TX_BUFFER_SIZE;
    settings->i2c_settings->pca9555_reg_map = storage->pca9555_reg_map;
    settings->i2c_settings->pca9555_num_registers = PCA9555_NUM_REGISTERS;

    I2C_Callbacks i2c_callbacks = {.i2c_process_received_data = pca9555_process_received_data, .i2c_process_address = pca9555_process_address};
    i2c_init(settings->i2c_settings, PCA9555, &i2c_callbacks);
}

void pca9555_process_received_data(I2C_Settings *settings, I2C_FSM *i2c_fsm)
{
    // Only one byte was received, so it was a write before read operation
    if (settings->hi2c->XferCount == settings->hi2c->XferSize - 1)
    {
        // Use the received register to pre-load the response
        uint8_t reg_to_read = settings->rx_data[0];
        settings->tx_data[0] = settings->pca9555_reg_map[reg_to_read].register_value;

        i2c_fsm->i2c_slave_state = PCA9555_SLAVE_RX;
    }
    // Handling a multi-byte write operation
    else if (settings->hi2c->XferCount == 0)
    {
        if (i2c_fsm->i2c_slave_state == PCA9555_SLAVE_RX)
        {
            // Write the value into the register map
            uint8_t reg_to_write = settings->rx_data[0];
            uint8_t data_to_write = settings->rx_data[1];
            settings->pca9555_reg_map[reg_to_write].register_value = data_to_write;
            // prv_pca9555_send_i2c_write_update_event(reg_to_write, data_to_write);
        }

        i2c_fsm->i2c_slave_select = I2C_NO_SLAVE;
        i2c_fsm->i2c_slave_state = I2C_IDLE;
    }

    // memset(settings->rx_data, 0, settings->rx_buffer_size);

    HAL_I2C_EnableListen_IT(settings->hi2c);
}

void pca9555_process_address(I2C_Settings *settings, I2C_FSM *i2c_fsm, I2C_Callback_Info *cb_info)
{
    uint8_t i2c_slave_address = cb_info->i2c_slave_address;
    uint8_t transfer_direction = cb_info->transfer_direction;

    if (transfer_direction == I2C_TX)
    {
        // Master is transmitting and slave needs to receive
        HAL_I2C_Slave_Seq_Receive_IT(settings->hi2c, settings->rx_data, PCA9555_I2C_NUM_BYTES_TO_RECEIVE, I2C_FIRST_FRAME);

        i2c_fsm->i2c_slave_select = PCA9555;
        i2c_fsm->i2c_slave_state = PCA9555_SLAVE_RX;
    }
    else if (transfer_direction == I2C_RX)
    {
        // Master is requesting data and slave needs to send
        HAL_I2C_Slave_Seq_Transmit_IT(settings->hi2c, settings->tx_data, PCA9555_I2C_NUM_BYTES_TO_SEND, I2C_FIRST_AND_LAST_FRAME);

        i2c_fsm->i2c_slave_state = PCA9555_SLAVE_TX;
    }
}

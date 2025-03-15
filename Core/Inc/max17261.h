/*
 * max17261.h
 *
 *  Created on: Feb 27, 2025
 *      Author: arvin
 */

#ifndef INC_MAX17261_H_
#define INC_MAX17261_H_

#include <stdint.h>

#include "i2c_defs.h"
#include "i2c_slave.h"
#include "max17261_defs.h"

#define MAX_NUM_MAX17261 2

#define MAX17261_I2C_ADDRESS 0x36
#define MAX17261_NUM_REGISTERS 255

#define MAX17261_I2C_RX_BUFFER_SIZE 3
#define MAX17261_I2C_NUM_BYTES_TO_RECEIVE MAX17261_I2C_RX_BUFFER_SIZE
#define MAX17261_I2C_TX_BUFFER_SIZE 3
#define MAX17261_I2C_NUM_BYTES_TO_SEND MAX17261_I2C_TX_BUFFER_SIZE

#define MAX17261_I2C_PORT I2C_PORT_2

typedef struct
{
    I2C_Settings *i2c_settings;
} MAX17261_Settings;

typedef struct
{
    uint8_t rx_data[MAX17261_I2C_RX_BUFFER_SIZE];
    uint8_t tx_data[MAX17261_I2C_TX_BUFFER_SIZE];
    MAX17261_Register_Map max17261_reg_map[MAX17261_NUM_REGISTERS];
} MAX17261_Storage;

void max17261_init_reg_map();
void max17261_init(MAX17261_Settings *settings, MAX17261_Storage *storage);
void max17261_process_received_data(I2C_Settings *settings, I2C_FSM *i2c_fsm);
void max17261_process_address(I2C_Settings *settings, I2C_FSM *i2c_fsm, I2C_Callback_Info *cb_info);

#endif /* INC_MAX17261_H_ */

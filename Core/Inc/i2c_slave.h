/*
 * i2c_slave.h
 *
 *  Created on: Feb 20, 2025
 *      Author: arvin
 */

#ifndef INC_I2C_SLAVE_H_
#define INC_I2C_SLAVE_H_

#include "main.h"
#include "i2c_defs.h"
#include "i2c_slave_fsm_defs.h"

#include <stdint.h>

#define I2C_TX I2C_DIRECTION_TRANSMIT
#define I2C_RX I2C_DIRECTION_RECEIVE

#define NUM_I2C_ADDRESSES 128

typedef enum
{
    I2C_PORT_1,
    I2C_PORT_2,
    NUM_I2C_PORTS
} I2C_PORTS;

typedef enum
{
    I2C_SLAVE_1,
    I2C_SLAVE_2,
    NUM_I2C_SLAVES
} I2C_SLAVE_IDS;

typedef struct
{
    I2C_SLAVE_FSM_STATES i2c_slave_state;
    I2C_SLAVE_SELECT i2c_slave_select;
} I2C_FSM;

typedef struct
{
    I2C_HandleTypeDef *hi2c;
    uint8_t i2c_slave_address;
    I2C_SLAVE_IDS i2c_slave_id;
    TIM_HandleTypeDef *htim;
    uint8_t *rx_data;
    uint8_t rx_buffer_size;
    uint8_t *tx_data;
    uint8_t tx_buffer_size;
    // TODO: Move to relevant storage structs
    PCA9555_Register_Map *pca9555_reg_map;
    uint8_t pca9555_num_registers;
    MAX17261_Register_Map *max17261_reg_map;
    uint8_t max17261_num_registers;
} I2C_Settings;

typedef struct
{
    uint8_t transfer_direction;
    uint8_t i2c_slave_address;
} I2C_Callback_Info;

typedef struct
{
    void (*i2c_process_received_data)(I2C_Settings *, I2C_FSM *);
    void (*i2c_process_address)(I2C_Settings *, I2C_FSM *, I2C_Callback_Info *);
} I2C_Callbacks;

void i2c_init(I2C_Settings *settings, I2C_SLAVE_SELECT slave_select, I2C_Callbacks *cbs);

#endif /* INC_I2C_SLAVE_H_ */

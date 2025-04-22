/*
 * pca9555.h
 *
 *  Created on: Feb 21, 2025
 *      Author: arvin
 */

#ifndef INC_PCA9555_H_
#define INC_PCA9555_H_

#include <stdint.h>

#include "i2c_defs.h"
#include "i2c_slave.h"
#include "pca9555_defs.h"

#define MAX_NUM_PCA9555 2

#define PCA9555_1_I2C_ADDRESS 0x20
#define PCA9555_2_I2C_ADDRESS 0x21
#define PCA9555_NUM_REGISTERS 8

#define PCA9555_I2C_RX_BUFFER_SIZE 2
#define PCA9555_I2C_NUM_BYTES_TO_RECEIVE PCA9555_I2C_RX_BUFFER_SIZE
#define PCA9555_I2C_TX_BUFFER_SIZE 2
#define PCA9555_I2C_NUM_BYTES_TO_SEND PCA9555_I2C_TX_BUFFER_SIZE

#define PCA9555_I2C_PORT I2C_PORT_1

typedef struct
{
    I2C_Settings *i2c_settings;
    I2C_Storage *i2c_storage;
} PCA9555_Settings;

typedef struct
{
    uint8_t rx_data[PCA9555_I2C_RX_BUFFER_SIZE];
    uint8_t tx_data[PCA9555_I2C_TX_BUFFER_SIZE];
    PCA9555_Register_Map pca9555_reg_map[PCA9555_NUM_REGISTERS];
    uint8_t pca9555_num_registers;
} PCA9555_Storage;

void pca9555_init(PCA9555_Settings *settings, PCA9555_Storage *storage);
void pca9555_process_address(I2C_Settings *settings, I2C_Storage *storage, I2C_FSM *i2c_fsm, I2C_Callback_Info *cb_info);
void pca9555_process_received_data(I2C_Settings *settings, I2C_Storage *storage, I2C_FSM *i2c_fsm);

#endif /* INC_PCA9555_H_ */

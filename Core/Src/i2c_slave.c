/*
 * i2c_slave.c
 *
 *  Created on: Feb 20, 2025
 *      Author: arvin
 */

#include "main.h"
#include "i2c_slave.h"
#include "i2c_defs.h"
#include "i2c_slave_fsm_defs.h"

#include <string.h>
#include <stdbool.h>

static volatile I2C_FSM i2c_fsm_state[NUM_I2C_SLAVE_DEVICES];
static volatile I2C_Settings i2c_settings[NUM_I2C_SLAVE_DEVICES];
static volatile I2C_Storage i2c_storage[NUM_I2C_SLAVE_DEVICES];
static uint8_t i2c_address_mapping[NUM_I2C_ADDRESSES] = {0};
static I2C_Callbacks i2c_callbacks[NUM_I2C_SLAVE_DEVICES];

// Develop an I2C receive state machine to keep track of how many bytes to receive, send, etc based on the peripheral that we are trying to simulate

void i2c_init(I2C_Settings *settings, I2C_Storage *storage, I2C_SLAVE_SELECT slave_select, I2C_Callbacks *cbs)
{
	uint8_t i2c_index = settings->i2c_slave_id;
	memcpy(&(i2c_settings[i2c_index]), settings, sizeof(I2C_Settings));
	memcpy(&(i2c_storage[i2c_index]), storage, sizeof(I2C_Storage));
	memcpy(&(i2c_callbacks[i2c_index]), cbs, sizeof(I2C_Callbacks));

	i2c_address_mapping[settings->i2c_slave_address] = settings->i2c_slave_id;

	i2c_fsm_state[i2c_index].i2c_slave_state = I2C_IDLE;
	i2c_fsm_state[i2c_index].i2c_slave_select = slave_select;

	HAL_I2C_EnableListen_IT(settings->hi2c);
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	uint8_t i2c_index = (hi2c == i2c_settings[0].hi2c) ? 0 : 1;

	i2c_callbacks[i2c_index].i2c_process_received_data(&(i2c_settings[i2c_index]), &(i2c_storage[i2c_index]), &i2c_fsm_state[i2c_index]);
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	uint16_t i2c_slave_address = AddrMatchCode >> 1;
	uint8_t i2c_index = i2c_address_mapping[i2c_slave_address];

	I2C_Callback_Info cb_info = {.transfer_direction = TransferDirection, .i2c_slave_address = i2c_slave_address};

	i2c_callbacks[i2c_index].i2c_process_address(&(i2c_settings[i2c_index]), &(i2c_storage[i2c_index]), &i2c_fsm_state[i2c_index], &cb_info);
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	uint8_t i2c_index = (hi2c == i2c_settings[0].hi2c) ? 0 : 1;

	i2c_fsm_state[i2c_index].i2c_slave_select = I2C_NO_SLAVE;
	i2c_fsm_state[i2c_index].i2c_slave_state = I2C_IDLE;
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
	// TODO: Handle I2C Errors
	HAL_I2C_EnableListen_IT(hi2c);
}

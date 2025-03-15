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

static volatile I2C_FSM i2c_fsm_state[NUM_I2C_SLAVES];
static volatile I2C_Settings i2c_settings[NUM_I2C_SLAVES];
static uint8_t i2c_address_mapping[NUM_I2C_ADDRESSES] = {0};
static I2C_Callbacks i2c_callbacks[NUM_I2C_SLAVES];

static inline void prv_i2c_get_index(I2C_HandleTypeDef *hi2c, uint8_t *i2c_index)
{
	*i2c_index = (hi2c == i2c_settings[0].hi2c) ? 0 : 1;
}

// Develop an I2C receive state machine to keep track of how many bytes to receive, send, etc based on the peripheral that we are trying to simulate

void i2c_init(I2C_Settings *settings, I2C_SLAVE_SELECT slave_select, I2C_Callbacks *cbs)
{
	uint8_t i2c_index = settings->i2c_slave_id;
	memcpy(&(i2c_settings[i2c_index]), settings, sizeof(I2C_Settings));
	memcpy(&(i2c_callbacks[i2c_index]), cbs, sizeof(I2C_Callbacks));

	i2c_address_mapping[settings->i2c_slave_address] = settings->i2c_slave_id;

	i2c_fsm_state[i2c_index].i2c_slave_state = I2C_IDLE;
	i2c_fsm_state[i2c_index].i2c_slave_select = slave_select;

	HAL_I2C_EnableListen_IT(settings->hi2c);
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	uint8_t i2c_index = (hi2c == i2c_settings[0].hi2c) ? 0 : 1;
//	prv_i2c_get_index(hi2c, &i2c_index);

	i2c_callbacks[i2c_index].i2c_process_received_data(&(i2c_settings[i2c_index]), &i2c_fsm_state[i2c_index]);

	// // Check if it was a true write or write for read before updating registers/pre-loading response
	// if (hi2c->XferCount == hi2c->XferSize - 1)
	// {
	// 	// Use the received register to pre-load the response
	// 	if (i2c_slave == PCA9555)
	// 	{
	// 		uint8_t reg_to_read = data_to_receive[0];
	// 		for (uint8_t i = 0; i < PCA9555_NUM_REGISTERS; i++)
	// 		{
	// 			if ((pca9555_reg_map[i].register_address) == reg_to_read)
	// 			{
	// 				data_to_send[0] = pca9555_reg_map[i].register_value;
	// 				break;
	// 			}
	// 		}

	// 		i2c_slave_state = PCA9555_SLAVE_RX;
	// 	}
	// 	else if (i2c_slave == MAX17261)
	// 	{
	// 		uint8_t reg_to_read = data_to_receive[0];
	// 		for (uint8_t i = 0; i < MAX17261_NUM_REGISTERS; i++)
	// 		{
	// 			if ((max17261_reg_map[i].register_address) == reg_to_read)
	// 			{
	// 				data_to_send[0] = max17261_reg_map[i].register_value & 0xFF;
	// 				data_to_send[1] = (max17261_reg_map[i].register_value >> 8) & 0xFF;
	// 				break;
	// 			}
	// 		}

	// 		i2c_slave_state = MAX17261_SLAVE_RX;
	// 	}
	// }
	// else if (hi2c->XferCount == 0)
	// {
	// 	// Write value into register map
	// 	if (i2c_slave_state == PCA9555_SLAVE_RX)
	// 	{
	// 		uint8_t reg_to_write = data_to_receive[0];
	// 		uint16_t byte_to_write = data_to_receive[1];
	// 		for (uint8_t i = 0; i < PCA9555_NUM_REGISTERS; i++)
	// 		{
	// 			if ((pca9555_reg_map[i].register_address) == reg_to_write)
	// 			{
	// 				pca9555_reg_map[i].register_value = byte_to_write;
	// 				break;
	// 			}
	// 		}
	// 	}
	// 	else if (i2c_slave_state == MAX17261_SLAVE_RX)
	// 	{
	// 		uint8_t reg_to_write = data_to_receive[0];
	// 		uint16_t byte_to_write = ((uint16_t)data_to_receive[2] << 8) | data_to_receive[1];
	// 		for (uint8_t i = 0; i < MAX17261_NUM_REGISTERS; i++)
	// 		{
	// 			// Check MSB and LSB
	// 			if ((max17261_reg_map[i].register_address) == reg_to_write)
	// 			{
	// 				if (reg_to_write != 0xDB)
	// 				{
	// 					max17261_reg_map[i].register_value = byte_to_write;
	// 					break;
	// 				}
	// 			}
	// 		}
	// 	}

	// 	i2c_slave = I2C_NO_SLAVE;
	// 	i2c_slave_state = I2C_IDLE;
	// }

	// memset(data_to_receive, 0, RxSIZE);

	// HAL_I2C_EnableListen_IT(hi2c);
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	uint16_t i2c_slave_address = AddrMatchCode >> 1;
	uint8_t i2c_index = i2c_address_mapping[i2c_slave_address];

	I2C_Callback_Info cb_info = {.transfer_direction = TransferDirection, .i2c_slave_address = i2c_slave_address};

	i2c_callbacks[i2c_index].i2c_process_address(&(i2c_settings[i2c_index]), &i2c_fsm_state[i2c_index], &cb_info);

	// if (TransferDirection == I2C_DIRECTION_TRANSMIT)
	// {
	// 	// Master is transmitting
	// 	if (i2c_slave_address == PCA9555_I2C_ADDRESS)
	// 	{
	// 		HAL_I2C_Slave_Seq_Receive_IT(hi2c, data_to_receive, 2, I2C_FIRST_FRAME);
	// 		i2c_slave = PCA9555;
	// 		i2c_slave_state = PCA9555_SLAVE_RX;
	// 	}
	// 	else if (i2c_slave_address == MAX17261_I2C_ADDRESS)
	// 	{
	// 		HAL_I2C_Slave_Seq_Receive_IT(hi2c, data_to_receive, 3, I2C_FIRST_FRAME);
	// 		i2c_slave = MAX17261;
	// 		i2c_slave_state = MAX17261_SLAVE_RX;
	// 	}
	// }
	// else
	// {
	// 	// Master is requesting
	// 	if (i2c_slave == PCA9555)
	// 	{
	// 		i2c_slave_state = PCA9555_SLAVE_TX;
	// 		HAL_I2C_Slave_Seq_Transmit_IT(hi2c, data_to_send, 2, I2C_FIRST_AND_LAST_FRAME);
	// 	}
	// 	else if (i2c_slave == MAX17261)
	// 	{
	// 		i2c_slave_state = MAX17261_SLAVE_TX;
	// 		HAL_I2C_Slave_Seq_Transmit_IT(hi2c, data_to_send, 3, I2C_FIRST_AND_LAST_FRAME);
	// 	}
	// }
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	uint8_t i2c_index = 0;
	prv_i2c_get_index(hi2c, &i2c_index);

	i2c_fsm_state[i2c_index].i2c_slave_select = I2C_NO_SLAVE;
	i2c_fsm_state[i2c_index].i2c_slave_state = I2C_IDLE;

	// if (i2c_slave_state == PCA9555_SLAVE_TX || i2c_slave_state == MAX17261_SLAVE_TX)
	// {
	// 	i2c_slave = I2C_NO_SLAVE;
	// 	i2c_slave_state = I2C_IDLE;
	// }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
	// TODO: Handle I2C Errors
	HAL_I2C_EnableListen_IT(hi2c);
}

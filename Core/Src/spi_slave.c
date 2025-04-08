/*
 * spi_slave.c
 *
 *  Created on: Feb 28, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "spi_defs.h"
#include "spi_slave.h"
#include "spi_slave_fsm_defs.h"

static volatile SPI_FSM spi_fsm_state[NUM_SPI_SLAVE_PORTS];
static volatile SPI_Settings spi_settings[NUM_SPI_SLAVE_PORTS];
static SPI_Callbacks spi_callbacks[NUM_SPI_SLAVE_PORTS];

void spi_slave_init(SPI_Settings *settings, SPI_SLAVE_SELECT slave_select, SPI_Callbacks *cbs)
{
	uint8_t spi_index = settings->spi_port;
	memcpy(&(spi_settings[spi_index]), settings, sizeof(SPI_Settings));
	memcpy(&(spi_callbacks[spi_index]), cbs, sizeof(SPI_Callbacks));

	spi_settings[spi_index].cs_pin = settings->cs_pin;

	spi_fsm_state[spi_index].spi_slave_state = SPI_IDLE;
	spi_fsm_state[spi_index].spi_slave_select = slave_select;

	LL_SPI_SetMode(settings->spi_handle, LL_SPI_MODE_SLAVE);
	LL_SPI_EnableIT_RXNE(settings->spi_handle);
	// LL_SPI_EnableIT_TXE(settings->spi_handle);
	LL_SPI_EnableIT_ERR(settings->spi_handle);
	LL_SPI_Enable(settings->spi_handle);
}

// TODO: Change the spi_index values for > 2 SPI devices if necessary (2 is the current max)
void spi_slave_rx_cb(SPI_TypeDef *spi_handle)
{
	uint8_t spi_index = (spi_settings[0].spi_handle == spi_handle) ? SPI_PORT_1 : SPI_PORT_2;

	if (spi_fsm_state[spi_index].spi_slave_state == SPI_TRANSACTION)
	{
		__HAL_TIM_SET_COUNTER(spi_settings[spi_index].timer_handle, 0);
	}
	else
	{
		HAL_TIM_Base_Start_IT(spi_settings[spi_index].timer_handle);
	}

	uint8_t next_index = spi_settings[spi_index].rx_index;
	if (next_index >= spi_settings[spi_index].rx_buffer_size)
	{
		next_index = 0;
	}

	spi_settings[spi_index].rx_data[next_index] = LL_SPI_ReceiveData8(spi_settings[spi_index].spi_handle);
	spi_settings[spi_index].rx_index += 1;

	// Process byte that is received
	// if (spi_settings[spi_index].rx_index == 1 || spi_settings[spi_index].rx_byte_callback)
	// {
	spi_callbacks[spi_index].spi_byte_process_cb(&(spi_settings[spi_index]));
	// }

	spi_fsm_state[spi_index].spi_slave_state = SPI_TRANSACTION;
}

void spi_slave_tx_cb(SPI_TypeDef *spi_handle)
{
	// TODO: Check what's wrong with multi-byte response
	uint8_t spi_index = (spi_settings[0].spi_handle == spi_handle) ? SPI_PORT_1 : SPI_PORT_2;

	if (spi_settings[spi_index].tx_index < spi_settings[spi_index].bytes_to_send)
	{
		uint8_t next_index = spi_settings[spi_index].tx_index;
		LL_SPI_TransmitData8(spi_settings[spi_index].spi_handle, spi_settings[spi_index].tx_data[next_index]);
		spi_settings[spi_index].tx_data[next_index] = 0;
		spi_settings[spi_index].tx_index += 1;
	}

	if (spi_settings[spi_index].tx_index == spi_settings[spi_index].bytes_to_send)
	{
		spi_settings[spi_index].tx_index = 0;
		spi_settings[spi_index].bytes_to_send = 0;
		LL_SPI_DisableIT_TXE(spi_settings[spi_index].spi_handle);
	}
	// spi_fsm_state[spi_index].spi_slave_state = SPI_SLAVE_TX;
}

void spi_slave_transfer_error_cb(SPI_TypeDef *spi_handle)
{
	// TODO: Handle errors in SPI transmission
	uint8_t spi_index = (spi_settings[0].spi_handle == spi_handle) ? SPI_PORT_1 : SPI_PORT_2;
	// spi_fsm_state[spi_index].spi_slave_state = SPI_ERROR;
}

// Timer to re-enable listening for SPI messages and handle the incrementing of timer
void spi_timer_cb(TIM_HandleTypeDef *timer_handle)
{
	uint8_t spi_index = (spi_settings[0].timer_handle == timer_handle) ? SPI_PORT_1 : SPI_PORT_2;

	// Check for end of SPI Rx Transaction
	if (spi_index < NUM_SPI_SLAVE_PORTS)
	{
		if (spi_fsm_state[spi_index].spi_slave_state == SPI_TRANSACTION)
		{
			if (LL_GPIO_IsInputPinSet(spi_settings[spi_index].cs_pin->gpio_port, spi_settings[spi_index].cs_pin->gpio_pin))
			{
				// Transaction has completed, so process data packet and reset everything
				spi_callbacks[spi_index].spi_rx_process_cb(&(spi_settings[spi_index]));

				HAL_TIM_Base_Stop_IT(spi_settings[spi_index].timer_handle);
				spi_settings[spi_index].rx_index = 0;
				spi_settings[spi_index].tx_index = 0;
				spi_settings[spi_index].bytes_to_send = 0;
				spi_fsm_state[spi_index].spi_slave_state = SPI_IDLE;
			}
		}
	}
}

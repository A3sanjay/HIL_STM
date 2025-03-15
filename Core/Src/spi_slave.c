/*
 * spi_slave.c
 *
 *  Created on: Feb 28, 2025
 *      Author: arvin
 */

#include "main.h"
#include "spi_defs.h"
#include "spi_slave.h"
#include "spi_slave_fsm_defs.h"

#include <stdbool.h>
#include <string.h>

static volatile SPI_FSM spi_fsm_state[NUM_SPI_PORTS];
static volatile SPI_Settings spi_settings[NUM_SPI_PORTS];
static void (*spi_process_byte)(SPI_Settings *);
static void (*spi_process_received_data)(SPI_Settings *);

extern TIM_HandleTypeDef htim3;

void spi_init(SPI_Settings *settings, SPI_SLAVE_SELECT slave_select, void (*spi_rx_process_cb)(SPI_Settings *), void (*spi_byte_process_cb)(SPI_Settings *))
{
	uint8_t spi_index = settings->spi_port;
	memcpy(&(spi_settings[spi_index]), settings, sizeof(SPI_Settings));
	spi_process_received_data = spi_rx_process_cb;
	spi_process_byte = spi_byte_process_cb;

	spi_fsm_state[spi_index].spi_slave_state = SPI_IDLE;
	spi_fsm_state[spi_index].spi_slave_select = slave_select;

	LL_SPI_SetMode(settings->spi_handle, LL_SPI_MODE_SLAVE);
	LL_SPI_EnableIT_RXNE(settings->spi_handle);
	// LL_SPI_EnableIT_TXE(settings->spi_handle);
	LL_SPI_EnableIT_ERR(settings->spi_handle);
	LL_SPI_Enable(settings->spi_handle);
}

void spi2_rx_cb(SPI_TypeDef *spi_handle)
{
	uint8_t spi_index = SPI_PORT_2;

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

	// Process the byte if it is the first byte (command byte) or an important byte
	if (spi_settings[spi_index].rx_index == 1 || spi_settings[spi_index].rx_byte_callback)
	{
		spi_process_byte(&(spi_settings[spi_index]));
	}

	spi_fsm_state[spi_index].spi_slave_state = SPI_TRANSACTION;
}

void spi2_tx_cb(SPI_TypeDef *spi_handle)
{
	uint8_t spi_index = SPI_PORT_2;

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

void spi2_transfererror_cb(SPI_TypeDef *spi_handle)
{
	// TODO: Handle errors in SPI transmission
	uint8_t spi_index = SPI_PORT_2;
	// spi_fsm_state[spi_index].spi_slave_state = SPI_ERROR;
}

// Timer to re-enable listening for SPI messages
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// Check for end of SPI Rx Transaction
	if (htim == &htim3)
	{
		uint8_t spi_index = SPI_PORT_2;
		if (spi_fsm_state[spi_index].spi_slave_state == SPI_TRANSACTION)
		{
			if (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_12))
			{
				spi_process_received_data(&(spi_settings[spi_index]));

				HAL_TIM_Base_Stop_IT(&htim3);
				spi_settings[spi_index].rx_index = 0;
				spi_settings[spi_index].tx_index = 0;
				spi_settings[spi_index].bytes_to_send = 0;
				spi_fsm_state[spi_index].spi_slave_state = SPI_IDLE;
			}
		}
	}
}

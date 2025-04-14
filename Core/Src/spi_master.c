/*
 * spi_master.c
 *
 *  Created on: Mar. 18, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "spi_master.h"

#include "gpio_defs.h"

static volatile SPI_Settings spi_master_settings[NUM_SPI_MASTER_PORTS];

void spi_master_init(SPI_Settings *settings)
{
    uint8_t spi_index = settings->spi_port;
    memcpy(&(spi_master_settings[spi_index]), settings, sizeof(SPI_Settings));

    LL_SPI_SetMode(settings->spi_handle, LL_SPI_MODE_MASTER);
    LL_SPI_EnableIT_ERR(settings->spi_handle);
    LL_SPI_Enable(settings->spi_handle);
}

void spi_master_transmit_buffer(SPI_Settings *settings, SPI_Storage *storage)
{
    // Drive the CS pin low, transmit the message, then drive it high again
    HAL_GPIO_WritePin(settings->cs_pin->gpio_port, settings->cs_pin->gpio_pin, GPIO_PIN_RESET);

    for (int8_t i = storage->bytes_to_send - 1; i >= 0; i--)
    {
        while (!LL_SPI_IsActiveFlag_TXE(settings->spi_handle))
        {
        }

        LL_SPI_TransmitData8(settings->spi_handle, storage->tx_data[i]);
    }

    while (LL_SPI_IsActiveFlag_BSY(settings->spi_handle))
    {
    }

    HAL_GPIO_WritePin(settings->cs_pin->gpio_port, settings->cs_pin->gpio_pin, GPIO_PIN_SET);
}

/*
 * mcp4811.c
 *
 *  Created on: Mar. 18, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "mcp4811.h"
#include "spi_master.h"
#include "spi_slave.h"

// Driver to control the MCP4811 10-bit DAC used to simulate analog signals sent to the controller board

static void prv_mcp4811_set_enable(uint16_t *tx_buffer)
{
    // Set enable bit
    uint16_t val_to_set = EN_MSG_TRUE << EN_MSG_BIT_POS;
    *tx_buffer |= val_to_set;
}

static void prv_mcp4811_set_disable(uint16_t *tx_buffer)
{
    // Set disable bit
    uint16_t val_to_set = EN_MSG_FALSE << EN_MSG_BIT_POS;
    *tx_buffer |= val_to_set;
}

static void prv_mcp4811_set_gain_selection_1x(uint16_t *tx_buffer)
{
    uint16_t val_to_set = GAIN_1X_BIT_VAL << GA_BIT_POS;
    *tx_buffer |= val_to_set;
}

static void prv_mcp4811_set_gain_selection_2x(uint16_t *tx_buffer)
{
    uint16_t val_to_set = GAIN_2X_BIT_VAL << GA_BIT_POS;
    *tx_buffer |= val_to_set;
}

static void prv_mcp4811_set_shutdown_device_active(uint16_t *tx_buffer)
{
    uint16_t val_to_set = SHDN_DEVICE_ACTIVE_BIT_VAL << SHDN_BIT_POS;
    *tx_buffer |= val_to_set;
}

static void prv_mcp4811_set_shutdown_device_off(uint16_t *tx_buffer)
{
    uint16_t val_to_set = SHDN_DEVICE_OFF_BIT_VAL << SHDN_BIT_POS;
    *tx_buffer |= val_to_set;
}

static void prv_mcp4811_convert_voltage_to_output(float desired_voltage, float *output, uint16_t *tx_buffer)
{
    if (desired_voltage < 0 || desired_voltage > MAX_OUTPUT_VOLTAGE)
    {
        // Set the enable bit to 0, the desired voltage is invalid, so maintain the DAC's current output voltage
        prv_mcp4811_set_disable(tx_buffer);
        return;
    }

    *output = ((desired_voltage * (float)(1 << DAC_PRECISION)) / V_REF);
}

static void prv_mcp4811_send_message(MCP4811_Settings *settings, uint16_t *tx_data, uint8_t data_length)
{
    memcpy(settings->spi_settings->tx_data, tx_data, data_length);
    settings->spi_settings->bytes_to_send = data_length;
    spi_master_transmit_buffer(settings->spi_settings);
}

void mcp4811_init(MCP4811_Settings *settings, MCP4811_Storage *storage)
{
    settings->spi_settings->tx_data = storage->tx_data;
    settings->spi_settings->tx_buffer_size = MCP4811_SPI_TX_BUFFER_SIZE;

    spi_master_init(settings->spi_settings);
}

void mcp4811_set_voltage(MCP4811_Settings *settings, MCP4811_Storage *storage, float voltage)
{
    uint16_t tx_data = 0;
    prv_mcp4811_set_shutdown_device_active(&tx_data);
    prv_mcp4811_set_enable(&tx_data);

    float output = 0;
    prv_mcp4811_convert_voltage_to_output(voltage, &output, &tx_data);

    // Set voltage according to input
    if (voltage > V_REF)
    {
        // Set the Gain Selection to 2x
        prv_mcp4811_set_gain_selection_2x(&tx_data);
        output /= 2;
    }
    else
    {
        // Keep the Gain Selection at 1x for increased accuracy
        prv_mcp4811_set_gain_selection_1x(&tx_data);
    }

    uint16_t data_chunk = (uint16_t)output & ((1 << NUM_DATA_BITS) - 1);
    tx_data |= (data_chunk << INPUT_DATA_BYTES_START_BIT_POS);

    prv_mcp4811_send_message(settings, &tx_data, sizeof(tx_data));
}

void mcp4811_shutdown_dac(MCP4811_Settings *settings, MCP4811_Storage *storage)
{
    uint16_t tx_data = 0;
    prv_mcp4811_set_shutdown_device_off(&tx_data);
    prv_mcp4811_set_enable(&tx_data);

    prv_mcp4811_send_message(settings, &tx_data, sizeof(tx_data));
}

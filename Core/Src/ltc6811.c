/*
 * ltc6811.c
 *
 *  Created on: Mar 30, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "spi_slave.h"
#include "ltc6811.h"
#include "crc15.h"

static LTC6811_Register_Map initial_ltc6811_reg_map[LTC6811_NUM_DEVICES][LTC6811_NUM_GROUPS];

static void set_tx_info(SPI_Settings *settings, uint8_t data_length)
{
    settings->tx_index = 0;
    settings->bytes_to_send = data_length * LTC6811_NUM_DEVICES;
    settings->rx_byte_callback = false;
}

static void preload_tx_info(SPI_Settings *settings, uint8_t *data, uint8_t data_length, uint8_t data_offset)
{
    // Use offset to determine which device to copy data to
    memcpy(settings->tx_data + (data_offset * data_length), data, data_length);
}

static bool command_byte_mask(uint16_t command_byte, uint16_t command_mask)
{
    if (((command_byte & command_mask) != 0) || (command_mask == 0))
        return true;

    return false;
}

static uint8_t prv_process_command_byte(uint16_t command_byte)
{
    // Voltage conversion command
    if (command_byte_mask(command_byte, LTC6811_ADCV_RESERVED) && command_byte_mask(command_byte, LTC6811_CNVT_CELL_ALL))
        return VOLTAGE_CONVERSION;

    // Temp conversion command
    if (command_byte_mask(command_byte, LTC6811_ADAX_RESERVED) && command_byte_mask(command_byte, LTC6811_ADAX_GPIO4))
        return TEMP_CONVERSION;

    // Voltage read command(s)
    if (command_byte_mask(command_byte, LTC6811_RDCVA_RESERVED))
        return VOLTAGE_READ_A;
    else if (command_byte_mask(command_byte, LTC6811_RDCVB_RESERVED))
        return VOLTAGE_READ_B;
    else if (command_byte_mask(command_byte, LTC6811_RDCVC_RESERVED))
        return VOLTAGE_READ_C;
    else if (command_byte_mask(command_byte, LTC6811_RDCVD_RESERVED))
        return VOLTAGE_READ_D;

    // Temp read command(s)
    if (command_byte_mask(command_byte, LTC6811_RDAUXA_RESERVED))
        return TEMP_READ_A;
    else if (command_byte_mask(command_byte, LTC6811_RDAUXB_RESERVED))
        return TEMP_READ_B;

    return 0;
}

static void ltc6811_init_reg_map()
{
    memset(initial_ltc6811_reg_map, 0, sizeof(initial_ltc6811_reg_map));
}

void ltc6811_init(LTC6811_Settings *settings, LTC6811_Storage *storage)
{
    ltc6811_init_reg_map();

    memcpy(storage->ltc6811_reg_map, initial_ltc6811_reg_map, sizeof(initial_ltc6811_reg_map));

    settings->spi_settings->rx_data = storage->rx_data;
    settings->spi_settings->rx_index = 0;
    settings->spi_settings->rx_buffer_size = LTC6811_SPI_RX_BUFFER_SIZE;
    settings->spi_settings->tx_data = storage->tx_data;
    settings->spi_settings->tx_index = 0;
    settings->spi_settings->tx_buffer_size = LTC6811_SPI_TX_BUFFER_SIZE;
    // settings->spi_settings->ltc6811_reg_map = storage->ltc6811_reg_map;
    settings->spi_settings->ltc6811_num_registers = LTC6811_NUM_REGISTERS;

    SPI_Callbacks spi_callbacks = {.spi_byte_process_cb = ltc6811_process_byte, .spi_rx_process_cb = ltc6811_process_received_data};

    spi_slave_init(settings->spi_settings, LTC6811, &spi_callbacks);

    crc15_init_table();
}

void ltc6811_process_byte(SPI_Settings *settings)
{
    // Exit early if this byte does not need to be processed
    if (settings->rx_index != LTC6811_COMMAND_BYTE_END_INDEX && settings->rx_index != LTC6811_PEC_END_INDEX && !settings->rx_byte_callback)
    {
        return;
    }

    uint16_t command_byte = 0;
    command_byte |= settings->rx_data[0] << 8;
    command_byte |= settings->rx_data[1];

    // Will probably have to "process" command byte first
    LTC6811_COMMAND_REQUEST_TYPE command_type = prv_process_command_byte(command_byte);

    // Handle read instructions based on command_type
    // TODO: Validate PEC before sending response data back
    switch (command_type)
    {
    case VOLTAGE_READ_A:
        if (settings->rx_index == LTC6811_COMMAND_BYTE_END_INDEX)
        {
            for (uint8_t i = 0; i < LTC6811_NUM_DEVICES; i++)
            {
                preload_tx_info(settings, settings->ltc6811_reg_map[i][VOLTAGE_GROUP_A].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH, i);
            }

            set_tx_info(settings, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (settings->rx_index == LTC6811_PEC_END_INDEX)
            LL_SPI_EnableIT_TXE(settings->spi_handle);

        break;
    case VOLTAGE_READ_B:
        if (settings->rx_index == LTC6811_COMMAND_BYTE_END_INDEX)
        {
            for (uint8_t i = 0; i < LTC6811_NUM_DEVICES; i++)
            {
                preload_tx_info(settings, settings->ltc6811_reg_map[i][VOLTAGE_GROUP_B].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH, i);
            }

            set_tx_info(settings, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (settings->rx_index == LTC6811_PEC_END_INDEX)
            LL_SPI_EnableIT_TXE(settings->spi_handle);

        break;
    case VOLTAGE_READ_C:
        if (settings->rx_index == LTC6811_COMMAND_BYTE_END_INDEX)
        {
            for (uint8_t i = 0; i < LTC6811_NUM_DEVICES; i++)
            {
                preload_tx_info(settings, settings->ltc6811_reg_map[i][VOLTAGE_GROUP_C].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH, i);
                set_tx_info(settings, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
            }

            set_tx_info(settings, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (settings->rx_index == LTC6811_PEC_END_INDEX)
            LL_SPI_EnableIT_TXE(settings->spi_handle);

        break;
    case VOLTAGE_READ_D:
        if (settings->rx_index == LTC6811_COMMAND_BYTE_END_INDEX)
        {
            for (uint8_t i = 0; i < LTC6811_NUM_DEVICES; i++)
            {
                preload_tx_info(settings, settings->ltc6811_reg_map[i][VOLTAGE_GROUP_D].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH, i);
            }

            set_tx_info(settings, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (settings->rx_index == LTC6811_PEC_END_INDEX)
            LL_SPI_EnableIT_TXE(settings->spi_handle);

        break;
    case TEMP_READ_A:
        if (settings->rx_index == LTC6811_COMMAND_BYTE_END_INDEX)
        {
            for (uint8_t i = 0; i < LTC6811_NUM_DEVICES; i++)
            {
                preload_tx_info(settings, settings->ltc6811_reg_map[i][TEMP_GROUP_A].ltc6811_reg_group.ltc6811_reg_data, LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH, i);
            }

            set_tx_info(settings, LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH);
        }
        else if (settings->rx_index == LTC6811_PEC_END_INDEX)
            LL_SPI_EnableIT_TXE(settings->spi_handle);

        break;
    case TEMP_READ_B:
        if (settings->rx_index == LTC6811_COMMAND_BYTE_END_INDEX)
        {
            for (uint8_t i = 0; i < LTC6811_NUM_DEVICES; i++)
            {
                preload_tx_info(settings, settings->ltc6811_reg_map[i][TEMP_GROUP_B].ltc6811_reg_group.ltc6811_reg_data, LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH, i);
            }

            set_tx_info(settings, LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH);
        }
        else if (settings->rx_index == LTC6811_PEC_END_INDEX)
            LL_SPI_EnableIT_TXE(settings->spi_handle);

        break;
    }
}

void ltc6811_process_received_data(SPI_Settings *settings)
{
    // Handle write instructions
    uint16_t command_byte = 0;
    command_byte |= settings->rx_data[0] << 8;
    command_byte |= settings->rx_data[1];

    uint8_t num_bytes_received = settings->rx_index;
    uint8_t reg = 0;

    LTC6811_COMMAND_REQUEST_TYPE command_type = prv_process_command_byte(command_byte);

    // Handle read instructions based on command_type
    // TODO: Validate PEC before filling in data
    switch (command_type)
    {
    case VOLTAGE_CONVERSION:;
        // TODO: Change simulation readings from fixed to dynamic (maybe according to some control algorithm). Make this data unique across voltage groups and across the number of devices that we support
        uint8_t voltage_group_packet[LTC6811_VOLTAGE_LENGTH] = {LTC6811_VOLTAGE_DEFAULT_VAL_HIGH_BYTE, LTC6811_VOLTAGE_DEFAULT_VAL_LOW_BYTE, LTC6811_VOLTAGE_DEFAULT_VAL_HIGH_BYTE, LTC6811_VOLTAGE_DEFAULT_VAL_LOW_BYTE, LTC6811_VOLTAGE_DEFAULT_VAL_HIGH_BYTE, LTC6811_VOLTAGE_DEFAULT_VAL_LOW_BYTE};
        uint16_t voltage_pec = crc15_calculate(voltage_group_packet, sizeof(voltage_group_packet));

        // Fill in the data in reg map for every voltage group across all our devices
        for (uint8_t i = 0; i < LTC6811_NUM_DEVICES; i++)
        {
            for (uint8_t j = 0; j < NUM_REG_MAP_GROUPS - 2; j++)
            {
                memcpy(settings->ltc6811_reg_map[i][j].ltc6811_reg_group.ltc6811_reg_data, voltage_group_packet, sizeof(voltage_group_packet));
                memcpy(settings->ltc6811_reg_map[i][j].ltc6811_reg_group.ltc6811_reg_data + LTC6811_VOLTAGE_LENGTH, &voltage_pec, sizeof(voltage_pec));
            }
        }

        break;
    case TEMP_CONVERSION:;
        // TODO: Change simulation readings from fixed to dynamic (maybe according to some control algorithm). Make this data unique across temp groups and across the number of devices that we support
        uint8_t temp_group_packet[LTC6811_TEMP_LENGTH] = {LTC6811_TEMP_DEFAULT_VAL_HIGH_BYTE, LTC6811_TEMP_DEFAULT_VAL_LOW_BYTE, LTC6811_TEMP_DEFAULT_VAL_HIGH_BYTE, LTC6811_TEMP_DEFAULT_VAL_LOW_BYTE, LTC6811_TEMP_DEFAULT_VAL_HIGH_BYTE, LTC6811_TEMP_DEFAULT_VAL_LOW_BYTE};
        uint16_t temp_pec = crc15_calculate(temp_group_packet, sizeof(temp_group_packet));

        // Fill in the data in reg map for every temp group across all our devices
        for (uint8_t i = 0; i < LTC6811_NUM_DEVICES; i++)
        {
            for (uint8_t j = NUM_REG_MAP_GROUPS - 2; j < NUM_REG_MAP_GROUPS; j++)
            {
                memcpy(settings->ltc6811_reg_map[i]->ltc6811_reg_group.ltc6811_reg_data, temp_group_packet, sizeof(temp_group_packet));
                memcpy(settings->ltc6811_reg_map[i]->ltc6811_reg_group.ltc6811_reg_data + LTC6811_TEMP_LENGTH, &temp_pec, sizeof(temp_pec));
            }
        }

        break;
    }
}

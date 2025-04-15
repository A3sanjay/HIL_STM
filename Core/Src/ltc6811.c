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

// Only one AFE will ever exist on our system
static LTC6811_Settings ltc6811_settings;
static LTC6811_Storage ltc6811_storage;

static void set_tx_info(SPI_Settings *settings, SPI_Storage *storage, uint8_t *data, uint8_t data_length)
{
    // We have to assign, but use this for assigning to reg_map
    storage->tx_data = data;
    storage->tx_index = 0;
    storage->bytes_to_send = data_length;
    settings->rx_byte_callback = false;
}

static bool command_byte_mask(uint16_t command_byte, uint16_t command_mask)
{
    if (((command_byte & command_mask) != 0) || (command_mask == 0))
        return true;

    return false;
}

static uint8_t prv_process_command_byte(uint16_t command_byte)
{
    // Temp conversion command
    if (command_byte_mask(command_byte, LTC6811_ADAX_RESERVED) && command_byte_mask(command_byte, LTC6811_ADAX_GPIO4))
        return TEMP_CONVERSION;

    // Voltage conversion command
    if (command_byte_mask(command_byte, LTC6811_ADCV_RESERVED) && command_byte_mask(command_byte, LTC6811_CNVT_CELL_ALL))
        return VOLTAGE_CONVERSION;

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

void ltc6811_init(LTC6811_Settings *settings, LTC6811_Storage *storage)
{
    memset(storage->ltc6811_reg_map, 0, sizeof(storage->ltc6811_reg_map));

    settings->spi_storage->rx_data = storage->rx_data;
    settings->spi_storage->rx_index = 0;
    settings->spi_storage->rx_buffer_size = LTC6811_SPI_RX_BUFFER_SIZE;
    settings->spi_storage->tx_data = storage->tx_data;
    settings->spi_storage->tx_index = 0;
    settings->spi_storage->bytes_to_send = 0;
    settings->spi_storage->tx_buffer_size = LTC6811_SPI_TX_BUFFER_SIZE;

    SPI_Callbacks spi_callbacks = {.spi_byte_process_cb = ltc6811_process_byte, .spi_rx_process_cb = ltc6811_process_received_data};

    spi_slave_init(settings->spi_settings, settings->spi_storage, LTC6811, &spi_callbacks);

    memcpy(&ltc6811_settings, settings, sizeof(LTC6811_Settings));
    memcpy(&ltc6811_storage, storage, sizeof(LTC6811_Storage));

    crc15_init_table();
}

void ltc6811_process_byte(SPI_Settings *settings, SPI_Storage *storage)
{
    // TODO: Can add early exit conditions to improve timing/performance of response (not all bytes have to be processed)

    uint8_t command_byte[LTC6811_CMD_BYTE_LENGTH] = {storage->rx_data[1], storage->rx_data[0]};

    // Will probably have to "process" command byte first
    LTC6811_COMMAND_REQUEST_TYPE command_type = prv_process_command_byte((command_byte[1] << 8) | command_byte[0]);

    // TODO: Check PEC of transmission after 4 bytes have been sent (for read commands). Since response will already be starting at this point even if PEC is invalid, set bytes_to_send to 0 for rest of transaction.
    if (storage->rx_index == LTC6811_PEC_END_INDEX)
    {
        // Validate PEC after received and exit if invalid
        uint16_t received_pec = (storage->rx_data[2] << 8) | storage->rx_data[3];
    }

    // Handle read instructions based on command_type
    switch (command_type)
    {
    case VOLTAGE_READ_A:
        if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_1)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[0][VOLTAGE_GROUP_A].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_2)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[1][VOLTAGE_GROUP_A].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_3)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[2][VOLTAGE_GROUP_A].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }

        break;
    case VOLTAGE_READ_B:
        if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_1)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[0][VOLTAGE_GROUP_B].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_2)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[1][VOLTAGE_GROUP_B].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_3)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[2][VOLTAGE_GROUP_B].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }

        break;
    case VOLTAGE_READ_C:
        if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_1)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[0][VOLTAGE_GROUP_C].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_2)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[1][VOLTAGE_GROUP_C].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_3)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[2][VOLTAGE_GROUP_C].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }

        break;
    case VOLTAGE_READ_D:
        if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_1)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[0][VOLTAGE_GROUP_D].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_2)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[1][VOLTAGE_GROUP_D].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_3)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[2][VOLTAGE_GROUP_D].ltc6811_reg_group.ltc6811_reg_data, LTC6811_VOLTAGE_RESPONSE_MESSAGE_LENGTH);
        }

        break;
    case TEMP_READ_A:
        if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_1)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[0][TEMP_GROUP_A].ltc6811_reg_group.ltc6811_reg_data, LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_2)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[1][TEMP_GROUP_A].ltc6811_reg_group.ltc6811_reg_data, LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_3)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[2][TEMP_GROUP_A].ltc6811_reg_group.ltc6811_reg_data, LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH);
        }

        break;
    case TEMP_READ_B:
        if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_1)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[0][TEMP_GROUP_B].ltc6811_reg_group.ltc6811_reg_data, LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_2)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[1][TEMP_GROUP_B].ltc6811_reg_group.ltc6811_reg_data, LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH);
        }
        else if (storage->rx_index == LTC6811_READ_PRELOAD_INDEX_DEVICE_3)
        {
            set_tx_info(settings, storage, ltc6811_storage.ltc6811_reg_map[2][TEMP_GROUP_B].ltc6811_reg_group.ltc6811_reg_data, LTC6811_TEMP_RESPONSE_MESSAGE_LENGTH);
        }

        break;
    }
}

void ltc6811_process_received_data(SPI_Settings *settings, SPI_Storage *storage)
{
    // Handle write instructions
    uint8_t command_byte[LTC6811_CMD_BYTE_LENGTH] = {storage->rx_data[0], storage->rx_data[1]};

    uint8_t num_bytes_received = storage->rx_index;
    uint8_t reg = 0;

    LTC6811_COMMAND_REQUEST_TYPE command_type = prv_process_command_byte((command_byte[0] << 8) | command_byte[1]);
    // Validate PEC after received and exit if invalid
    uint16_t received_pec = (storage->rx_data[2] << 8) | storage->rx_data[3];
    if (received_pec != crc15_calculate(command_byte, LTC6811_CMD_BYTE_LENGTH))
    {
        return;
    }

    // Handle read instructions based on command_type
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
                memcpy(ltc6811_storage.ltc6811_reg_map[i][j].ltc6811_reg_group.ltc6811_reg_data, voltage_group_packet, sizeof(voltage_group_packet));
                memcpy(ltc6811_storage.ltc6811_reg_map[i][j].ltc6811_reg_group.ltc6811_reg_data + LTC6811_VOLTAGE_LENGTH, &voltage_pec, sizeof(voltage_pec));
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
                memcpy(ltc6811_storage.ltc6811_reg_map[i]->ltc6811_reg_group.ltc6811_reg_data, temp_group_packet, sizeof(temp_group_packet));
                memcpy(ltc6811_storage.ltc6811_reg_map[i]->ltc6811_reg_group.ltc6811_reg_data + LTC6811_TEMP_LENGTH, &temp_pec, sizeof(temp_pec));
            }
        }

        break;
    }
}

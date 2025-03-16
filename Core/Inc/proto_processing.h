/*
 * proto_processing.h
 *
 *  Created on: Mar 15, 2025
 *      Author: arvin
 */

#ifndef INC_PROTO_PROCESSING_H_
#define INC_PROTO_PROCESSING_H_

#include <stdint.h>
#include <stdbool.h>

#define MIN_BOARD_RESPONSE_BUFFER_SIZE 20
#define BOARD_RESPONSE_MESSAGE_NOT_RECEIVED 0
#define BOARD_RESPONSE_MESSAGE_RECEIVED 1

#define MIN_I2C_WRITE_UPDATE_EVENT_BUFFER_SIZE 50
#define MIN_SPI_WRITE_UPDATE_EVENT_BUFFER_SIZE 100

typedef struct
{
    uint8_t *buffer;
    uint8_t buffer_length;
    uint8_t encoded_data_length;
} Proto_Storage;

typedef struct
{
    uint32_t peripheral_to_update;
    uint32_t i2c_address;
    uint32_t register_to_update;
    uint32_t value_to_write;
} I2C_Write_Update_Event;

typedef struct
{
    uint32_t peripheral_to_update;
    uint32_t *registers_to_update;
    uint32_t *values_to_write;
} SPI_Write_Update_Event;

void proto_process_decode_board_init(uint8_t *raw_data, uint8_t raw_data_length, uint32_t *board_to_run);
void proto_process_encode_board_response(Proto_Storage *storage);
void proto_process_encode_i2c_write_update_event(I2C_Write_Update_Event *i2c_event, Proto_Storage *storage);
void proto_process_encode_spi_write_update_event(SPI_Write_Update_Event *spi_event, Proto_Storage *storage);

#endif /* INC_PROTO_PROCESSING_H_ */

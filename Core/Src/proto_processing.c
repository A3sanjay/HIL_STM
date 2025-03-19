/*
 * proto_processing.c
 *
 *  Created on: Mar 15, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <stdbool.h>

#include "proto_processing.h"
#include <pb_encode.h>
#include <pb_decode.h>
#include "set_board_response.pb.h"
#include "update_event_message.pb.h"

// Handle the encoding and decoding of various messages using the ProtoBuf framework

void proto_process_decode_board_init(Proto_Decode_Storage *storage)
{
    InitializeBoard message = InitializeBoard_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(storage->buffer_to_decode, storage->buffer_to_decode_length);
    bool status = pb_decode(&stream, InitializeBoard_fields, &message);
    memcpy(storage->decoded_output, &message, sizeof(InitializeBoard));
}

void proto_process_encode_board_response(Board_Response *response, Proto_Encode_Storage *storage)
{
    if (storage->buffer_to_encode_length < MIN_BOARD_RESPONSE_BUFFER_SIZE)
    {
        return;
    }

    Response message = Response_init_zero;
    pb_ostream_t stream = pb_ostream_from_buffer(storage->buffer_to_encode, storage->buffer_to_encode_length);
    message.message_received = response->acknowledgement;
    bool status = pb_encode(&stream, Response_fields, &message);
    storage->encoded_buffer_length = stream.bytes_written;
}

void proto_process_encode_i2c_write_update_event(I2C_Write_Update_Event *i2c_event, Proto_Encode_Storage *storage)
{
    if (storage->buffer_to_encode_length < MIN_I2C_WRITE_UPDATE_EVENT_BUFFER_SIZE)
    {
        return;
    }

    I2CWriteEvent message = I2CWriteEvent_init_zero;
    pb_ostream_t stream = pb_ostream_from_buffer(storage->buffer_to_encode, storage->buffer_to_encode_length);

    message.peripheral_to_update = i2c_event->peripheral_to_update;
    message.i2c_address = i2c_event->i2c_address;
    message.register_to_update = i2c_event->register_to_update;
    message.value_to_write = i2c_event->value_to_write;

    bool status = pb_encode(&stream, I2CWriteEvent_fields, &message);
    storage->encoded_buffer_length = stream.bytes_written;
}

void proto_process_encode_spi_write_update_event(SPI_Write_Update_Event *spi_event, Proto_Encode_Storage *storage)
{
    if (storage->buffer_to_encode_length < MIN_SPI_WRITE_UPDATE_EVENT_BUFFER_SIZE)
    {
        return;
    }

    SPIWriteEvent message = SPIWriteEvent_init_zero;
    pb_ostream_t stream = pb_ostream_from_buffer(storage->buffer_to_encode, storage->buffer_to_encode_length);

    message.peripheral_to_update = spi_event->peripheral_to_update;
    // TODO: Give some more thought on what the variable length fields look like (how the registers are structured, etc)
    message.registers_to_update.arg = spi_event->registers_to_update;
    message.values_to_write.arg = spi_event->values_to_write;

    bool status = pb_encode(&stream, SPIWriteEvent_fields, &message);
    storage->encoded_buffer_length = stream.bytes_written;
}

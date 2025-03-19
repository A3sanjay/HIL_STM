/*
 * proto_handling.c
 *
 *  Created on: Mar 17, 2025
 *      Author: arvin
 */

// #include <stdint.h>
// #include <stdbool.h>

// #include "proto_handling.h"
// #include "proto_processing.h"

// // Handle any receive/send operation over ProtoBuf. Can implement more fancy queue reception, ...

// // TODO: Do error handling, null checking, etc
// void handle_proto_message(Proto_Message_Info *message_info, Proto_Message_Storage *storage, void *event_object)
// {
//     // Check the type of message
//     if (message_info->message_type == PROTO_BOARD_SETUP_MESSAGE)
//     {
//         // Prepare decoding of status message
//         Proto_Decode_Storage *decode_storage = storage->decode_storage;
//         proto_process_decode_board_init(decode_storage);
//     }
//     else if (message_info->message_type == PROTO_RESPONSE_MESSAGE)
//     {
//         // Prepare a response message
//         Board_Response *board_response = (Board_Response *)event_object;
//         Proto_Encode_Storage *encode_storage = storage->encode_storage;
//         proto_process_encode_board_response(board_response, encode_storage);
//     }
//     else if (message_info->message_type == PROTO_EVENT_UPDATE_MESSAGE)
//     {
//         // If event update, check if I2C or SPI (write) event update
//         if (message_info->event_update_type == PROTO_I2C_WRITE_EVENT_UPDATE)
//         {
//             I2C_Write_Update_Event *i2c_event = (I2C_Write_Update_Event *)event_object;
//             Proto_Encode_Storage *encode_storage = storage->encode_storage;
//             proto_process_encode_i2c_write_update_event(i2c_event, encode_storage);
//         }
//         else if (message_info->event_update_type == PROTO_SPI_WRITE_EVENT_UPDATE)
//         {
//             SPI_Write_Update_Event *spi_event = (SPI_Write_Update_Event *)event_object;
//             Proto_Encode_Storage *encode_storage = storage->encode_storage;
//             proto_process_encode_spi_write_update_event(spi_event, encode_storage);
//         }
//     }
// }

// void send_proto_message()
// {
// }
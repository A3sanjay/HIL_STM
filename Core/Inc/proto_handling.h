/*
 * proto_handling.h
 *
 *  Created on: Mar 17, 2025
 *      Author: arvin
 */

#ifndef INC_PROTO_HANDLING_H_
#define INC_PROTO_HANDLING_H_

// #include <stdint.h>
// #include <stdbool.h>

// #include "proto_processing.h"

// typedef enum
// {
//     PROTO_OPERATION_ENCODE,
//     PROTO_OPERATION_DECODE,
//     NUM_PROTO_OPERATION_TYPES
// } PROTO_OPERATION_TYPE;

// typedef enum
// {
//     PROTO_BOARD_SETUP_MESSAGE,
//     PROTO_RESPONSE_MESSAGE,
//     PROTO_EVENT_UPDATE_MESSAGE,
//     NUM_PROTO_MESSAGE_TYPES
// } PROTO_MESSAGE_TYPE;

// typedef enum
// {
//     PROTO_I2C_WRITE_EVENT_UPDATE,
//     PROTO_SPI_WRITE_EVENT_UPDATE,
//     NUM_PROTO_EVENT_UPDATE_TYPES
// } PROTO_EVENT_UPDATE_TYPE;

// typedef struct
// {
//     PROTO_MESSAGE_TYPE message_type;
//     PROTO_OPERATION_TYPE operation_type;
//     PROTO_EVENT_UPDATE_TYPE event_update_type;
// } Proto_Message_Info;

// typedef struct
// {
//     Proto_Encode_Storage *encode_storage;
//     Proto_Decode_Storage *decode_storage;
// } Proto_Message_Storage;

// void handle_proto_message(Proto_Message_Info *message_info, Proto_Message_Storage *storage, void *event_object);

#endif /* INC_PROTO_HANDLING_H_ */

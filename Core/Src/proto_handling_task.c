/*
 * proto_handling_task.c
 *
 *  Created on: Mar 17, 2025
 *      Author: arvin
 */

// #include <stdint.h>
// #include <stdbool.h>

// #include "proto_handling_task.h"
// #include "proto_handling.h"

// static Proto_Task_Storage proto_storage;

// void proto_handling_task_init(Proto_Task_Storage *storage)
// {
//     storage->proto_queue = xQueueCreate(PROTO_TASK_QUEUE_LENGTH, PROTO_TASK_QUEUE_ITEM_SIZE);
//     xTaskCreate(proto_task_run, "Proto Handling Task", NORMAL_STACK_DEPTH, NULL, NORMAL_PRIORITY, storage->proto_task);

//     memcpy(&proto_storage, storage, sizeof(Proto_Task_Storage));
// }

// void proto_task_run(void *params)
// {
//     // Wait for proto command
//     Proto_Task_Info message_to_receive;
//     xQueueReceive(proto_storage.proto_queue, &message_to_receive, BLOCK_INDEFINITELY);

//     Proto_Message_Info *message_info = message_to_receive.message_info;
//     Proto_Message_Storage *message_storage = message_to_receive.message_storage;
//     void *event_object = message_to_receive.event_object;

//     // Process ProtoBuf message
//     handle_proto_message(message_info, message_storage, event_object);
// }
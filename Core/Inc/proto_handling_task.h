/*
 * proto_handling_task.h
 *
 *  Created on: Mar 17, 2025
 *      Author: arvin
 */

// #ifndef INC_PROTO_HANDLING_TASK_H_
// #define INC_PROTO_HANDLING_TASK_H_

// #include <stdint.h>
// #include <stdbool.h>

// #include "free_rtos_support.h"
// #include "uart.h"

// #define PROTO_TASK_QUEUE_LENGTH 10
// #define PROTO_TASK_QUEUE_ITEM_SIZE sizeof(Proto_Message_Storage)

// typedef struct
// {
//     TaskHandle_t *proto_task;
//     QueueHandle_t *proto_queue;
//     SemaphoreHandle_t *proto_semaphore;
//     Uart_sett
// } Proto_Task_Storage;

// typedef struct
// {
//     Proto_Message_Info *message_info;
//     Proto_Message_Storage *message_storage;
//     void *event_object;
// } Proto_Task_Info;

// void proto_handling_task_init(Proto_Task_Storage *storage);
// void proto_task_run(void *params);

#endif /* INC_PROTO_HANDLING_TASK_H_ */

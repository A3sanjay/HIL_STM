/*
 * free_rtos_support.h
 *
 *  Created on: Mar 16, 2025
 *      Author: arvin
 */

#ifndef INC_FREE_RTOS_SUPPORT_H_
#define INC_FREE_RTOS_SUPPORT_H_

#include <stdint.h>
#include <limits.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#define MINIMAL_STACK_DEPTH configMINIMAL_STACK_SIZE
#define NORMAL_STACK_DEPTH ((uint16_t)256)
#define LARGE_STACK_DEPTH ((uint16_t)512)

#define LOWEST_PRIORITY 0
#define NORMAL_PRIORITY 1
#define HIGHEST_PRIORITY (configMAX_PRIORITIES - 1)

#define BLOCK_INDEFINITELY portMAX_DELAY

#define TRUE pdTRUE
#define FALSE pdFALSE

#define NOTIFY_NO_EVENT_BITS 0x0000
#define NOTIFY_CLEAR_EVENT_BITS ULONG_MAX

#define BOARD_INIT_TASK_NOTIFICATION_FLAG 0x0001

#endif /* INC_FREE_RTOS_SUPPORT_H_ */

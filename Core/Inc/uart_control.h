/*
 * uart_control.h
 *
 *  Created on: Mar 3, 2025
 *      Author: arvin
 */

#ifndef INC_UART_CONTROL_H_
#define INC_UART_CONTROL_H_

#include <stdint.h>

#include "main.h"
#include "uart.h"
#include "uart_control_fsm_defs.h"
#include "free_rtos_support.h"

#define START_BYTE 0xFC
#define INVALID_BYTE 0x00
#define END_BYTE 0xCF

// Macros for reception size in number of bytes
#define SETUP_START_BYTE_LENGTH 1
#define SETUP_DATA_LENGTH_BYTE_LENGTH 1
#define SETUP_DATA_BYTES_LENGTH 100
#define SETUP_CRC_BYTES_LENGTH 2
#define SETUP_END_BYTE_LENGTH 1

#define SETUP_MAX_UART_PACKET_LENGTH MAX_UART_PACKET_LENGTH
#define RESPONSE_UART_PACKET_LENGTH MAX_UART_PACKET_LENGTH

#define END_LINE_CHARACTER 0x0A

typedef struct
{
    UART_HandleTypeDef *huart;
    UART_Settings *uart_settings;
    uint8_t data_length;
    uint8_t raw_data[MAX_UART_PACKET_LENGTH];
    TaskHandle_t *uart_rx_cp_notify_task;
} UART_Control;

void uart_control_rx_init(UART_Control *control, void (*uart_receive_completed_callback)(UART_Control *control));
void uart_control_rx_start(UART_Control *control);
void uart_control_update_state(UART_Settings *settings);
void uart_control_rx_cb(UART_Settings *settings);
void uart_control_tx(UART_Settings *settings);
void uart_control_tx_add_end_line(uint8_t *buffer, uint8_t buffer_length);

#endif /* INC_UART_CONTROL_H_ */

/*
 * uart_control.h
 *
 *  Created on: Mar 3, 2025
 *      Author: arvin
 */

#ifndef INC_UART_CONTROL_H_
#define INC_UART_CONTROL_H_

#include <stdint.h>

#include "uart.h"
#include "uart_control_fsm_defs.h"

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

typedef struct
{
    UART_HandleTypeDef *huart;
    UART_Settings *uart_settings;
    uint8_t data_length;
    uint8_t raw_data[MAX_UART_PACKET_LENGTH];
} UART_Control;

void uart_control_board_init(UART_Control *uart_control);
void uart_control_update_state(UART_Settings *settings);
void uart_control_rx_cb(UART_Settings *settings);
void uart_control_handle_setup(UART_Settings *settings);

#endif /* INC_UART_CONTROL_H_ */

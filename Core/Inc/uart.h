/*
 * uart.h
 *
 *  Created on: Mar 3, 2025
 *      Author: arvin
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "uart_fsm_defs.h"

#include <stdint.h>

// Macros for reception size in number of bytes
#define SETUP_START_BYTE_LENGTH 1
#define SETUP_DATA_LENGTH_BYTE_LENGTH 1
#define SETUP_DATA_BYTES_LENGTH 100
#define SETUP_CRC_BYTES_LENGTH 2
#define SETUP_END_BYTE_LENGTH 1

typedef struct
{
    UART_HandleTypeDef *huart;
    uint8_t *start_byte;
    uint8_t *data_length_byte;
    uint8_t *data_bytes;
    uint8_t *crc_bytes;
    uint8_t *end_byte;
    uint8_t *rx_data;
    uint8_t bytes_to_receive;
    void (*transaction_cp_cb)(uint8_t *data_byte);
} UART_Settings;

void uart_init(UART_Settings *settings, void (*uart_rx_it_cb)(UART_Settings *, UART_FSM_STATES *), void (*uart_state_update)(UART_Settings *, UART_FSM_STATES *));
void uart_receive();

#endif /* INC_UART_H_ */

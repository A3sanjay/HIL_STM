/*
 * uart.h
 *
 *  Created on: Mar 3, 2025
 *      Author: arvin
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "uart_control_fsm_defs.h"

#include <stdint.h>

#define UART_TRANSMIT_TIMEOUT 5

#define MAX_UART_PACKET_LENGTH 100

typedef struct
{
    uint8_t rx_data[MAX_UART_PACKET_LENGTH];
    uint8_t tx_data[MAX_UART_PACKET_LENGTH];
} UART_Storage;

typedef struct
{
    UART_HandleTypeDef *huart;
    uint8_t *rx_data;
    uint8_t *tx_data;
    uint8_t bytes_to_receive;
    uint8_t bytes_to_send;
} UART_Settings;

typedef struct
{
    void (*uart_process_received_data)(UART_Settings *);
    void (*uart_update_state)(UART_Settings *);
    void (*transaction_cp_cb)(UART_Settings *);
} UART_Callbacks;

void uart_init(UART_Settings *settings, UART_Callbacks *callbacks);
void uart_receive();
void uart_transmit(UART_Settings *settings);

#endif /* INC_UART_H_ */

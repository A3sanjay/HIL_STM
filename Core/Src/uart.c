/*
 * uart.c
 *
 *  Created on: Mar 3, 2025
 *      Author: arvin
 */

#include "main.h"
#include "uart.h"
#include "uart_control_fsm_defs.h"

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

static volatile UART_Settings *uart_settings;
static UART_Storage uart_storage;
static UART_Callbacks uart_callbacks;

void uart_init(UART_Settings *settings, UART_Callbacks *callbacks)
{
    settings->rx_data = uart_storage.rx_data;
    settings->tx_data = uart_storage.tx_data;
    settings->bytes_to_receive = 0;
    settings->bytes_to_send = 0;

    uart_settings = settings;

    uart_callbacks.uart_process_received_data = callbacks->uart_process_received_data;
    uart_callbacks.uart_update_state = callbacks->uart_update_state;
    uart_callbacks.transaction_cp_cb = callbacks->transaction_cp_cb;
}

void uart_receive()
{
    uint8_t num_bytes_to_receive = uart_settings->bytes_to_receive;
    uint8_t *rx_buffer = uart_settings->rx_data;

    HAL_UART_Receive_IT(uart_settings->huart, rx_buffer, num_bytes_to_receive);
}

void uart_transmit(UART_Settings *settings)
{
    HAL_UART_Transmit(settings->huart, settings->tx_data, settings->bytes_to_send, UART_TRANSMIT_TIMEOUT);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uart_callbacks.uart_process_received_data(uart_settings);
    uart_callbacks.uart_update_state(uart_settings);
}

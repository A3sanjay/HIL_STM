/*
 * uart.c
 *
 *  Created on: Mar 3, 2025
 *      Author: arvin
 */

#include "main.h"
#include "uart.h"
#include "uart_fsm_defs.h"

#include <string.h>
#include <stdbool.h>

static volatile UART_FSM_STATES uart_fsm_state;
static volatile UART_Settings uart_settings;

static void (*uart_process_received_data)(UART_Settings *, UART_FSM_STATES *);
static void (*uart_update_state)(UART_Settings *, UART_FSM_STATES *);

void uart_init(UART_Settings *settings, void (*uart_rx_it_cb)(UART_Settings *, UART_FSM_STATES *), void (*uart_state_update)(UART_Settings *, UART_FSM_STATES *))
{
    memcpy(&uart_settings, settings, sizeof(UART_Settings));

    uart_process_received_data = uart_rx_it_cb;
    uart_update_state = uart_state_update;

    uart_fsm_state = UART_IDLE;
}

void uart_receive()
{
    uint8_t num_bytes_to_receive = uart_settings.bytes_to_receive;
    uint8_t *rx_buffer = uart_settings.rx_data;

    if (num_bytes_to_receive != 0)
    {
        HAL_UART_Receive_IT(uart_settings.huart, rx_buffer, num_bytes_to_receive);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uart_process_received_data(&uart_settings, &uart_fsm_state);
    uart_update_state(&uart_settings, &uart_fsm_state);
}

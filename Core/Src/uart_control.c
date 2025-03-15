/*
 * uart_control.c
 *
 *  Created on: Mar 3, 2025
 *      Author: arvin
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "uart.h"
#include "uart_control.h"

static Uart_Control uart_control;
static BOARD_TO_SIMULATE board = NONE;

void uart_control_board_init(Uart_Control *uart_control)
{
    memcpy(&uart_control, uart_control, sizeof(Uart_Control));

    uart_init(uart_control->uart_settings, uart_control_rx_cb, uart_control_update_state);
    uart_receive();
}

void uart_control_update_state(UART_Settings *settings, UART_FSM_STATES *uart_fsm_state)
{
    if (*uart_fsm_state == UART_IDLE)
    {
        *uart_fsm_state = SETUP_START_BYTE;
        settings->bytes_to_receive = SETUP_START_BYTE_LENGTH;
        settings->rx_data = settings->start_byte;
    }
    else if (*uart_fsm_state == SETUP_START_BYTE)
    {
        *uart_fsm_state = SETUP_DATA_LENGTH_BYTE;
        settings->bytes_to_receive = SETUP_DATA_LENGTH_BYTE_LENGTH;
        settings->rx_data = settings->data_length_byte;
    }
    else if (*uart_fsm_state == SETUP_DATA_LENGTH_BYTE)
    {
        *uart_fsm_state = SETUP_DATA_BYTES;
        settings->bytes_to_receive = settings->data_length_byte[0];
        settings->rx_data = settings->data_bytes;
    }
    else if (*uart_fsm_state == SETUP_DATA_BYTES)
    {
        *uart_fsm_state = SETUP_END_BYTE;
        settings->bytes_to_receive = SETUP_END_BYTE_LENGTH;
        settings->rx_data = settings->end_byte;
    }
    else if (*uart_fsm_state == SETUP_CRC_BYTES)
    {
        settings->bytes_to_receive = SETUP_CRC_BYTES_LENGTH;
        settings->rx_data = settings->crc_bytes;
    }
    else if (*uart_fsm_state == SETUP_END_BYTE)
    {
        *uart_fsm_state = SETUP_COMPLETE;
    }

    if (*uart_fsm_state != SETUP_COMPLETE)
    {
        uart_receive();
    }
}

void uart_control_rx_cb(UART_FSM_STATES *uart_fsm_state)
{
    switch (*uart_fsm_state)
    {
    case UART_IDLE:
        break;
    case SETUP_START_BYTE:
        if (uart_control.init_data_packet->start_byte[0] != START_BYTE)
        {
            *uart_fsm_state = UART_IDLE;
        }

        break;
    case SETUP_DATA_LENGTH_BYTE:
        if (uart_control.init_data_packet->data_length_byte[0] == INVALID_BYTE)
        {
            *uart_fsm_state = UART_IDLE;
        }

        break;
    case SETUP_DATA_BYTES:
        break;
    case SETUP_CRC_BYTES:
        break;
    case SETUP_END_BYTE:
        if (uart_control.init_data_packet->end_byte[0] != END_BYTE)
        {
            *uart_fsm_state = UART_IDLE;
        }

        break;
    case SETUP_COMPLETE:
        break;
    }
}

void uart_control_transaction_cb()
{
    // Add decoding logic here
}
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
#include "proto_processing.h"
#include "i2c_spi_periphs_control.h"

// Control module to manage UART communication with RPi
// TODO: Rx currently is only written for one "connection" at a time, and this design can be improved

static UART_Control uart_control;
static UART_CONTROL_FSM_STATES uart_fsm_state;
void (*uart_control_cp_cb)(UART_Control *control);

void uart_control_rx_init(UART_Control *control, void (*uart_receive_completed_callback)(UART_Control *control))
{
    memcpy(&uart_control, control, sizeof(UART_Control));

    uart_control.uart_settings->huart = control->huart;

    UART_Callbacks cbs = {.uart_process_received_data = uart_control_rx_cb, .uart_update_state = uart_control_update_state, .transaction_cp_cb = NULL};
    uart_init(uart_control.uart_settings, &cbs);

    uart_control_cp_cb = uart_receive_completed_callback;
}

void uart_control_rx_start(UART_Control *control)
{
    uart_fsm_state = UART_IDLE;
    uart_control_update_state(control->uart_settings);
}

void uart_control_update_state(UART_Settings *settings)
{
    if (uart_fsm_state == UART_IDLE)
    {
        uart_fsm_state = SETUP_START_BYTE;
        settings->bytes_to_receive = SETUP_START_BYTE_LENGTH;
    }
    else if (uart_fsm_state == SETUP_START_BYTE)
    {
        uart_fsm_state = SETUP_DATA_LENGTH_BYTE;
        settings->bytes_to_receive = SETUP_DATA_LENGTH_BYTE_LENGTH;
    }
    else if (uart_fsm_state == SETUP_DATA_LENGTH_BYTE)
    {
        uart_fsm_state = SETUP_DATA_BYTES;

        uint8_t data_length_byte = settings->rx_data[0];
        settings->bytes_to_receive = data_length_byte;
    }
    else if (uart_fsm_state == SETUP_DATA_BYTES)
    {
        uart_fsm_state = SETUP_END_BYTE;
        settings->bytes_to_receive = SETUP_END_BYTE_LENGTH;
    }
    else if (uart_fsm_state == SETUP_CRC_BYTES)
    {
        settings->bytes_to_receive = SETUP_CRC_BYTES_LENGTH;
    }
    else if (uart_fsm_state == SETUP_END_BYTE)
    {
        uart_fsm_state = SETUP_COMPLETE;
        uart_control_cp_cb(&uart_control);
    }

    if (uart_fsm_state != SETUP_COMPLETE)
    {
        uart_receive();
    }
}

void uart_control_rx_cb(UART_Settings *settings)
{
    switch (uart_fsm_state)
    {
    case UART_IDLE:
        break;
    case SETUP_START_BYTE:;
        uint8_t start_byte = uart_control.uart_settings->rx_data[0];
        if (start_byte != START_BYTE)
        {
            uart_fsm_state = UART_IDLE;
        }

        break;
    case SETUP_DATA_LENGTH_BYTE:;
        uint8_t data_length_byte = uart_control.uart_settings->rx_data[0];
        uart_control.data_length = data_length_byte;
        if (data_length_byte == INVALID_BYTE || data_length_byte == START_BYTE || data_length_byte == END_BYTE)
        {
            uart_fsm_state = UART_IDLE;
        }

        break;
    case SETUP_DATA_BYTES:
        // Just copy over data here. Processing can be done at the end of the transaction
        memcpy(uart_control.raw_data, uart_control.uart_settings->rx_data, uart_control.data_length);
        break;
    case SETUP_CRC_BYTES:
        // TODO: Use CRC to validate data packet
        break;
    case SETUP_END_BYTE:;
        uint8_t end_byte = uart_control.uart_settings->rx_data[0];
        if (end_byte != END_BYTE)
        {
            uart_fsm_state = UART_IDLE;
        }

        break;
    case SETUP_COMPLETE:
        break;
    }
}

// TODO: Make this thread-safe, as any thread can call it at any time
void uart_control_tx(UART_Settings *settings)
{
    uart_transmit(settings);
}

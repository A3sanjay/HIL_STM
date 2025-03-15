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
#include "uart_fsm_defs.h"

#define START_BYTE 0xFC
#define INVALID_BYTE 0x00
#define END_BYTE 0xCF

typedef enum
{
    NONE,
    POWER_DISTRIBUTION,
    CENTRE_CONSOLE,
    MCI,
    BMS
} BOARD_TO_SIMULATE;

typedef struct
{
    uint8_t start_byte[SETUP_START_BYTE_LENGTH];
    uint8_t data_length_byte[SETUP_DATA_LENGTH_BYTE_LENGTH];
    uint8_t data_bytes[SETUP_DATA_BYTES_LENGTH];
    uint8_t crc_bytes[SETUP_CRC_BYTES_LENGTH];
    uint8_t end_byte[SETUP_END_BYTE_LENGTH];
} Uart_Init_Data_Packet;

typedef struct
{
    UART_Settings *uart_settings;
    Uart_Init_Data_Packet *init_data_packet;
} Uart_Control;

void uart_control_board_init(Uart_Control *uart_control);
void uart_control_update_state(UART_Settings *settings, UART_FSM_STATES *uart_fsm_state);
void uart_control_rx_cb(UART_FSM_STATES *uart_fsm_state);
void uart_control_transaction_cb();

#endif /* INC_UART_CONTROL_H_ */

/*
 * uart_fsm_defs.h
 *
 *  Created on: Mar 3, 2025
 *      Author: arvin
 */

#ifndef INC_UART_FSM_DEFS_H_
#define INC_UART_FSM_DEFS_H_

typedef enum
{
    UART_IDLE,
    SETUP_START_BYTE,
    SETUP_DATA_LENGTH_BYTE,
    SETUP_DATA_BYTES,
    SETUP_CRC_BYTES,
    SETUP_END_BYTE,
    SETUP_COMPLETE
} UART_FSM_STATES;

#endif /* INC_UART_FSM_DEFS_H_ */

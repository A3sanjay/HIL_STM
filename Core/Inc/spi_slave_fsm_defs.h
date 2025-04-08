/*
 * spi_slave_fsm_defs.h
 *
 *  Created on: Mar 1, 2025
 *      Author: arvin
 */

#ifndef INC_SPI_SLAVE_FSM_DEFS_H_
#define INC_SPI_SLAVE_FSM_DEFS_H_

typedef enum
{
    SPI_IDLE,
    SPI_TRANSACTION,
    SPI_SLAVE_RX,
    SPI_SLAVE_TX,
    SPI_ERROR
} SPI_SLAVE_FSM_STATES;

typedef enum
{
    SPI_NO_SLAVE,
    MCP2515,
    LTC6811
} SPI_SLAVE_SELECT;

#endif /* INC_SPI_SLAVE_FSM_DEFS_H_ */

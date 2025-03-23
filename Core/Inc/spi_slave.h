/*
 * spi_slave.h
 *
 *  Created on: Feb 28, 2025
 *      Author: arvin
 */

#ifndef INC_SPI_SLAVE_H_
#define INC_SPI_SLAVE_H_

#include "main.h"
#include "spi_defs.h"
#include "spi_slave_fsm_defs.h"

#include <stdbool.h>

#define NUM_SPI_SLAVE_PORTS 2

typedef struct
{
    SPI_SLAVE_FSM_STATES spi_slave_state;
    SPI_SLAVE_SELECT spi_slave_select;
} SPI_FSM;

void spi_slave_init(SPI_Settings *settings, SPI_SLAVE_SELECT slave_select, void (*spi_rx_process_cb)(SPI_Settings *), void (*spi_byte_process_cb)(SPI_Settings *));

#endif /* INC_SPI_SLAVE_H_ */

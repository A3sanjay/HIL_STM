/*
 * i2c_spi_periphs_control.c
 *
 *  Created on: Feb 27, 2025
 *      Author: arvin
 */

#include "i2c_defs.h"
#include "i2c_slave.h"
#include "i2c_spi_periphs_control.h"
#include "pca9555.h"
#include "max17261.h"

static BOARDS_TO_SIMULATE curr_board = NO_BOARD;

static PCA9555_Settings pca9555_settings[MAX_NUM_PCA9555];
static PCA9555_Storage pca9555_storage[MAX_NUM_PCA9555];

static MAX17261_Settings max17261_settings[MAX_NUM_PCA9555];
static MAX17261_Storage max17261_storage[MAX_NUM_PCA9555];

static I2C_Settings i2c_settings[NUM_I2C_SLAVES];

void board_control_init()
{
    if (curr_board == POWER_DISTRIBUTION)
    {
        // Power Distribution has 2 x GPIO Expanders
        pca9555_settings[0].i2c_settings->i2c_slave_id = 0;
        pca9555_settings[0].i2c_settings = &i2c_settings[0];
        pca9555_init(&pca9555_settings[0], &pca9555_storage[0]);

        pca9555_settings[1].i2c_settings->i2c_slave_id = 1;
        pca9555_settings[1].i2c_settings = &i2c_settings[1];
        pca9555_init(&pca9555_settings[0], &pca9555_storage[1]);
    }
    else if (curr_board == CENTRE_CONSOLE)
    {
        // Centre Console has 2 x GPIO Expanders
        pca9555_settings[0].i2c_settings->i2c_slave_id = 0;
        pca9555_settings[0].i2c_settings = &i2c_settings[0];
        pca9555_init(&pca9555_settings[0], &pca9555_storage[0]);

        pca9555_settings[1].i2c_settings->i2c_slave_id = 1;
        pca9555_settings[1].i2c_settings = &i2c_settings[1];
        pca9555_init(&pca9555_settings[0], &pca9555_storage[1]);
    }
    else if (curr_board == MCI)
    {
        // MCI has 1 x SPI -> CAN converter
    }
    else if (curr_board == BMS)
    {
        // BMS has 1 x Current Sense + 1 x AFE
        max17261_settings[0].i2c_settings->i2c_slave_id = 0;
        max17261_settings[0].i2c_settings = &i2c_settings[0];
        max17261_init(&max17261_settings[0], &max17261_storage[0]);
    }
}

void set_board(BOARDS_TO_SIMULATE board)
{
    curr_board = board;
}

void switch_simulated_board()
{
}
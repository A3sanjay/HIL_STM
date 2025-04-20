/*
 * spi_slave.h
 *
 *  Created on: Feb 28, 2025
 *      Author: arvin
 */

#ifndef INC_SPI_SLAVE_H_
#define INC_SPI_SLAVE_H_

#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "spi_slave_fsm_defs.h"
#include "gpio_defs.h"

#define NUM_SPI_SLAVE_PORTS 2

#define SPI_TX_DEFAULT_VAL 0x00

#define SPI1_CS_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_15

#define SPI2_CS_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_12

#define LTC6811_NUM_GROUPS 6
#define LTC6811_NUM_BYTES_IN_REG_GROUP 8

typedef struct
{
    uint8_t register_value;
} MCP2515_Register_Map;

typedef struct
{
    uint8_t ltc6811_reg_data[LTC6811_NUM_BYTES_IN_REG_GROUP];
} LTC6811_Data_Register_Group;

typedef struct
{
    LTC6811_Data_Register_Group ltc6811_config_reg_group;                   // For config data (no PEC) - adcopt, swtrd, etc
    LTC6811_Data_Register_Group ltc6811_pwm_discharge_group;                // For PWM discharge info - TODO: figure out what to do with this later
    LTC6811_Data_Register_Group ltc6811_data_reg_group[LTC6811_NUM_GROUPS]; // Actual data (voltage + temp) - TODO: split up into 6 groups (4 for voltage and 2 for temp)
} LTC6811_Register_Map;

typedef enum
{
    SPI_PORT_1,
    SPI_PORT_2,
    SPI_PORT_3,
    SPI_PORT_4,
    NUM_SPI_PORTS
} SPI_PORTS;

typedef struct
{
    SPI_SLAVE_FSM_STATES spi_slave_state;
    SPI_SLAVE_SELECT spi_slave_select;
} SPI_FSM;

typedef struct
{
    SPI_TypeDef *spi_handle;
    GPIO_Pin *cs_pin;
    SPI_PORTS spi_port;
    TIM_HandleTypeDef *timer_handle;
    bool rx_byte_callback;
} SPI_Settings;

typedef struct
{
    uint8_t *rx_data;
    uint8_t rx_index;
    uint8_t rx_buffer_size;
    uint8_t *tx_data;
    uint8_t tx_index;
    uint8_t bytes_to_send;
    uint8_t tx_buffer_size;
} SPI_Storage;

typedef struct
{
    void (*spi_byte_process_cb)(SPI_Settings *, SPI_Storage *);
    void (*spi_rx_process_cb)(SPI_Settings *, SPI_Storage *);
} SPI_Callbacks;

void spi_slave_init(SPI_Settings *settings, SPI_Storage *storage, SPI_SLAVE_SELECT slave_select, SPI_Callbacks *cbs);

#endif /* INC_SPI_SLAVE_H_ */

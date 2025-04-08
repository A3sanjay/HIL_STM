/*
 * spi_defs.h
 *
 *  Created on: Mar 1, 2025
 *      Author: arvin
 */

#ifndef INC_SPI_DEFS_H_
#define INC_SPI_DEFS_H_

#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "gpio_defs.h"

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
} LTC6811_Register_Group;

typedef struct
{
	LTC6811_Register_Group ltc6811_reg_group;
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
	SPI_TypeDef *spi_handle;
	GPIO_Pin *cs_pin;
	SPI_PORTS spi_port;
	TIM_HandleTypeDef *timer_handle;
	uint8_t *rx_data;
	uint8_t rx_index;
	uint8_t rx_buffer_size;
	bool rx_byte_callback;
	uint8_t *tx_data;
	uint8_t tx_index;
	uint8_t bytes_to_send;
	uint8_t tx_buffer_size;
	// TODO: Move to MCP2151_Storage/LTC6811_Storage struct
	MCP2515_Register_Map *mcp2515_reg_map;
	LTC6811_Register_Map ltc6811_reg_map[3][LTC6811_NUM_GROUPS];
	uint8_t mcp2515_num_registers;
	uint8_t ltc6811_num_registers;
} SPI_Settings;

typedef struct
{
	void (*spi_byte_process_cb)(SPI_Settings *);
	void (*spi_rx_process_cb)(SPI_Settings *);
} SPI_Callbacks;

#endif /* INC_SPI_DEFS_H_ */

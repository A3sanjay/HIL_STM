/*
 * ltc6811_defs.h
 *
 *  Created on: Mar 30, 2025
 *      Author: arvin
 */

#ifndef INC_LTC6811_DEFS_H_
#define INC_LTC6811_DEFS_H_

typedef enum
{
    VOLTAGE_CONVERSION,
    TEMP_CONVERSION,
    VOLTAGE_READ_A,
    VOLTAGE_READ_B,
    VOLTAGE_READ_C,
    VOLTAGE_READ_D,
    TEMP_READ_A,
    TEMP_READ_B,
    NUM_COMMANDS
} LTC6811_COMMAND_REQUEST_TYPE;

typedef enum
{
    VOLTAGE_GROUP_A,
    VOLTAGE_GROUP_B, 
    VOLTAGE_GROUP_C,
    VOLTAGE_GROUP_D,
    TEMP_GROUP_A,
    TEMP_GROUP_B,
    NUM_REG_MAP_GROUPS
} LTC6811_REG_MAP_GROUPS;

#define LTC6811_NUM_REGISTERS 42

#define LTC6811_REG_DEFAULT_VAL 0x0000

// Command codes
// See Table 38 (p.59)
#define LTC6811_WRCFG_RESERVED (1 << 0)

#define LTC6811_RDCFG_RESERVED (1 << 1)

#define LTC6811_RDCVA_RESERVED (1 << 2)

#define LTC6811_RDCVB_RESERVED (1 << 2) | (1 << 1)

#define LTC6811_RDCVC_RESERVED (1 << 3)

#define LTC6811_RDCVD_RESERVED (1 << 3) | (1 << 1)

#define LTC6811_RDAUXA_RESERVED ((1 << 3) | (1 << 2))

#define LTC6811_RDAUXB_RESERVED ((1 << 3) | (1 << 2)) | (1 << 1)

#define LTC6811_RDSTATA_RESERVED (1 << 4)

#define LTC6811_RDSTATB_RESERVED (1 << 4) | (1 << 1)

#define LTC6811_ADCV_RESERVED ((1 << 9) | (1 << 6) | (1 << 5))

#define LTC6811_ADCOW_RESERVED ((1 << 3) | (1 << 5) | (1 << 9))

#define LTC6811_CVST_RESERVED ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 9))

#define LTC6811_ADAX_RESERVED (1 << 10) | (1 << 6) | (1 << 5)

#define LTC6811_CLRCELL_RESERVED (1 << 0) | (1 << 4) | (1 << 8) | (1 << 9) | (1 << 10)

#define LTC6811_CLRAUX_RESERVED (1 << 1) | (1 << 4) | (1 << 8) | (1 << 9) | (1 << 10)

#define LTC6811_CLRSTAT_RESERVED (1 << 0) | (1 << 1) | (1 << 4) | (1 << 8) | (1 << 9) | (1 << 10)

#define LTC6811_PLADC_RESERVED (1 << 2) | (1 << 4) | (1 << 8) | (1 << 9) | (1 << 10)

#define LTC6811_DIAGNC_RESERVED (1 << 0) | (1 << 2) | (1 << 4) | (1 << 8) | (1 << 9) | (1 << 10)

#define LTC6811_WRCOMM_RESERVED (1 << 0) | (1 << 5) | (1 << 8) | (1 << 9) | (1 << 10)

#define LTC6811_RDCOMM_RESERVED (1 << 1) | (1 << 5) | (1 << 8) | (1 << 9) | (1 << 10)

#define LTC6811_STCOMM_RESERVED (1 << 0) | (1 << 1) | (1 << 5) | (1 << 8) | (1 << 9) | (1 << 10)

#define LTC6811_WRPWM_RESERVED (1 << 5)

#define LTC6811_RDPWM_RESERVED (1 << 5) | (1 << 2)

// Command bits
// See Table 40 (p. 62)
#define LTC6811_GPIO1_PD_ON (0 << 3)
#define LTC6811_GPIO1_PD_OFF (1 << 3)
#define LTC6811_GPIO2_PD_ON (0 << 4)
#define LTC6811_GPIO2_PD_OFF (1 << 4)
#define LTC6811_GPIO3_PD_ON (0 << 5)
#define LTC6811_GPIO3_PD_OFF (1 << 5)
#define LTC6811_GPIO4_PD_ON (0 << 6)
#define LTC6811_GPIO4_PD_OFF (1 << 6)
#define LTC6811_GPIO5_PD_ON (0 << 7)
#define LTC6811_GPIO5_PD_OFF (1 << 7)

#define LTC6811_CNVT_CELL_ALL 0x00
#define LTC6811_CNVT_CELL_1_7 0x01
#define LTC6811_CNVT_CELL_2_8 0x02
#define LTC6811_CNVT_CELL_3_9 0x03
#define LTC6811_CNVT_CELL_4_10 0x04
#define LTC6811_CNVT_CELL_5_11 0x05
#define LTC6811_CNVT_CELL_6_12 0x06

#define LTC6811_ADCV_DISCHARGE_NOT_PERMITTED (0 << 4)
#define LTC6811_ADCV_DISCHARGE_PERMITTED (1 << 4)

#define LTC6811_ADCOPT (1 << 0)

#define LTC6811_SWTRD (1 << 1)

#define LTC6811_ADAX_GPIO1 0x01
#define LTC6811_ADAX_GPIO4 0x04
#define LTC6811_ADAX_MODE_FAST (0 << 8) | (1 << 7)

#define LTC6811_ICOM_CSBM_LOW (1 << 3)
#define LTC6811_ICOM_CSBM_HIGH (1 << 3) | (1 << 0)
#define LTC6811_ICOM_NO_TRANSMIT (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0)

#define LTC6811_FCOM_CSBM_LOW (0 << 0)
#define LTC6811_FCOM_CSBM_HIGH (1 << 3) | (1 << 0)

// See Table 17 (p. 38)
#define LTC6811_PWMC_DC_100 (0xF)

#endif /* INC_LTC6811_DEFS_H_ */

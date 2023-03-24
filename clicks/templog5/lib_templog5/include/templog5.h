/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for Temp-Log 5 Click driver.
 *
 * \addtogroup templog5 Temp-Log 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPLOG5_H
#define TEMPLOG5_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define TEMPLOG5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPLOG5_RETVAL  uint8_t

#define TEMPLOG5_OK           0x00
#define TEMPLOG5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup Register macros
 * \{
 */
#define TEMPLOG5_REG_CAPABILITY                      0x00
#define TEMPLOG5_REG_CONFIGURATION                   0x01
#define TEMPLOG5_REG_HIGH_LIMIT                      0x02
#define TEMPLOG5_REG_LOW_LIMIT                       0x03
#define TEMPLOG5_REG_CRITICAL_LIMIT                  0x04
#define TEMPLOG5_REG_TEMPERATURE                     0x05
#define TEMPLOG5_REG_MANUFACTURER_ID                 0x06
#define TEMPLOG5_REG_DEVICE_ID                       0x07
/** \} */

/**
 * \defgroup Configuration macros
 * \{
 */
#define TEMPLOG5_CFG_DISABLE_HYSTERESIS              0x0000
#define TEMPLOG5_CFG_HYSTERESIS_TO_1p5C              0x0200
#define TEMPLOG5_CFG_HYSTERESIS_TO_3C                0x0400
#define TEMPLOG5_CFG_HYSTERESIS_TO_6C                0x0600
#define TEMPLOG5_CFG_TEMP_SENSOR_ENABLE              0x0000
#define TEMPLOG5_CFG_TEMP_SENSOR_DISABLE             0x0100
#define TEMPLOG5_CFG_CRITICAL_TRIP_ENABLE            0x0000
#define TEMPLOG5_CFG_CRITICAL_TRIP_DISABLE           0x0080
#define TEMPLOG5_CFG_ALARM_TRIP_ENABLE               0x0000
#define TEMPLOG5_CFG_ALARM_TRIP_DISABLE              0x0040
#define TEMPLOG5_CFG_EVENT_INT_PIN_ENABLE            0x0010
#define TEMPLOG5_CFG_EVENT_INT_PIN_DISABLE           0x0000
#define TEMPLOG5_CFG_EVENT_OUT_ENABLE                0x0008
#define TEMPLOG5_CFG_EVENT_OUT_DISABLE               0x0000
#define TEMPLOG5_CFG_EVENT_OUT_ACTIVE_LOW            0x0000
#define TEMPLOG5_CFG_EVENT_OUT_ACTIVE_HIGH           0x0002
#define TEMPLOG5_CFG_EVENT_MODE_COMPARATOR           0x0000
#define TEMPLOG5_CFG_EVENT_MODE_INTERRUPT            0x0001
/** \} */

/**
 * \defgroup Capability macros
 * \{
 */
#define TEMPLOG5_CAP_EVSD_FROZEN                     0x0000
#define TEMPLOG5_CAP_EVSD_CLEARD                     0x0080
#define TEMPLOG5_CAP_TMOUT_10ms_60ms                 0x0000
#define TEMPLOG5_CAP_TMOUT_25ms_35ms                 0x0040
#define TEMPLOG5_CAP_RSWP_NOT_EXPLICITLY_STATED      0x0000
#define TEMPLOG5_CAP_RSWP_EXPLICITLY_STATED          0x0020
#define TEMPLOG5_CAP_TEMP_RES_9bit                   0x0000
#define TEMPLOG5_CAP_TEMP_RES_10bit                  0x0008
#define TEMPLOG5_CAP_TEMP_RES_11bit                  0x0010
#define TEMPLOG5_CAP_TEMP_RES_12bit                  0x0018
#define TEMPLOG5_CAP_POS_TEMP_ONLY                   0x0000
#define TEMPLOG5_CAP_POS_AND_NEG_TEMP                0x0004
#define TEMPLOG5_CAP_ACC_CLASS_C                     0x0000
#define TEMPLOG5_CAP_ACC_CLASS_B                     0x0002
#define TEMPLOG5_CAP_EV_CRITICAL_TEMP_ONLY           0x0000
#define TEMPLOG5_CAP_EV_ALARM_AND_CRITICAL_TEMP      0x0001
/** \} */

/**
 * \defgroup Temperature Sensor slave address macros
 * \{
 */
#define TEMPLOG5_TS_SLAVE_ADDR_000                   0x18
#define TEMPLOG5_TS_SLAVE_ADDR_001                   0x19
#define TEMPLOG5_TS_SLAVE_ADDR_010                   0x1A
#define TEMPLOG5_TS_SLAVE_ADDR_011                   0x1B
#define TEMPLOG5_TS_SLAVE_ADDR_100                   0x1C
#define TEMPLOG5_TS_SLAVE_ADDR_101                   0x1D
#define TEMPLOG5_TS_SLAVE_ADDR_110                   0x1E
#define TEMPLOG5_TS_SLAVE_ADDR_111                   0x1F
/** \} */

/**
 * \defgroup EEPROM slave address macros
 * \{
 */
#define TEMPLOG5_EEPROM_SLAVE_ADDR_000               0x50
#define TEMPLOG5_EEPROM_SLAVE_ADDR_001               0x51
#define TEMPLOG5_EEPROM_SLAVE_ADDR_010               0x52
#define TEMPLOG5_EEPROM_SLAVE_ADDR_011               0x53
#define TEMPLOG5_EEPROM_SLAVE_ADDR_100               0x54
#define TEMPLOG5_EEPROM_SLAVE_ADDR_101               0x55
#define TEMPLOG5_EEPROM_SLAVE_ADDR_110               0x56
#define TEMPLOG5_EEPROM_SLAVE_ADDR_111               0x57
/** \} */

/**
 * \defgroup Return value macros
 * \{
 */
#define TEMPLOG5_MANUFACTURER_ID                     0x1B09
#define TEMPLOG5_DEVICE_ID_REV_B                     0x0813
#define TEMPLOG5_DEVICE_ID_REV_C                     0x0A00
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t ts_slave;
    uint8_t eeprom_slave;
    uint8_t temp_status;

} templog5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t ts_slave;
    uint8_t eeprom_slave;


} templog5_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void templog5_cfg_setup ( templog5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPLOG5_RETVAL templog5_init ( templog5_t *ctx, templog5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for TempLog5 click.
 * 
 * @note
 * <pre>
 * TEMPLOG5_REG_CONFIGURATION:
 *   -TEMPLOG5_CFG_DISABLE_HYSTERESIS
 *   -TEMPLOG5_CFG_TEMP_SENSOR_ENABLE
 *   -TEMPLOG5_CFG_CRITICAL_TRIP_ENABLE
 *   -TEMPLOG5_CFG_ALARM_TRIP_ENABLE
 *   -TEMPLOG5_CFG_EVENT_INT_PIN_ENABLE
 *   -TEMPLOG5_CFG_EVENT_OUT_ENABLE
 *   -TEMPLOG5_CFG_EVENT_OUT_ACTIVE_HIGH
 *   -TEMPLOG5_CFG_EVENT_MODE_COMPARATOR
 * </pre>
 * 
 */
void templog5_default_cfg ( templog5_t *ctx );

/**
 * @brief Functions for write data to the TS register
 *
 * @param ctx          Click object.
 * @param reg          Register Address.
 * @param data_in      Data to be written in register.
 * 
 * @description This function write data data to the TS register
 */
void templog5_write_data ( templog5_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Writes data to the EEPROM address ( maximum 16 bytes per 1 page ).
 *
 *  Writting starts on given address.
 *
 * @param ctx           Click object.
 * @param start_addr    Start address.
 * @param data_in       Pointer to data.
 * @param n_byte        Number of bytes for writting.
 * 
 * @description This function write data to the EEPROM address .
 */
void templog5_write_eeprom ( templog5_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_byte );

/**
 * @brief Functions for read data from registers
 *
 * @param ctx            Click object.
 * @param reg            Register address.
 * 
 * @returns 16-bit data that is reads from the TS register.
 *
 * @description This function read from the TS register
 */
uint16_t templog5_read_data ( templog5_t *ctx, uint8_t reg );

/**
 * @brief Reads data from EEPROM.
 *
 * @param ctx             Click object.
 * @param start_addr      Eeprom start address.
 * @param data_out        Buffer to be filled with the data from eeprom.
 * @param n_byte          Number of bytes.
 * 
 * @description This function read data to the EEPROM address.
 */
void templog5_read_eeprom ( templog5_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_byte );

/**
 * @brief Temperature Data.
 *
 * @param ctx  Click object.
 * 
 * @returns Temperature data in C.
 * 
 * @description This function return temperature value.
 */
float templog5_get_temperature ( templog5_t *ctx );

/**
 * @brief Teperature Status.
 *
 * @param ctx  Click object.
 * 
 * @returns The first 4 bits in the temperature data register.
 * 
 * @description This function return temperature status.
 */
uint8_t templog5_get_temperature_status ( templog5_t *ctx );

/**
 * @brief EVENT Interrupt status.
 * 
 * @param ctx  Click object.
 *
 * @returns Interrupt status on the INT pin.
 * 
 * @description This function return interrupt status.
 */
uint8_t templog5_get_interrupt_status ( templog5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPLOG5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

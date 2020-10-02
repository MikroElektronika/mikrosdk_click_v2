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
 * \brief This file contains API for IrThermo 2 Click driver.
 *
 * \addtogroup irthermo2 IrThermo 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRTHERMO2_H
#define IRTHERMO2_H

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
#define IRTHERMO2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.al = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRTHERMO2_RETVAL  uint8_t

#define IRTHERMO2_OK           0x00
#define IRTHERMO2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup reg_i2c_addr Register I2C Address
 * \{
 */
 
/**
 * I2C address 0
 *
 * - ADDR1 : 0;
 * - ADDR0 : 0;
 */
#define IRTHERMO2_I2C_ADDRESS_0                                 0x40

/**
 * I2C address 1
 *
 * - ADDR1 : 0;
 * - ADDR0 : 1;
 */
#define IRTHERMO2_I2C_ADDRESS_1                                 0x41

/**
 * I2C address 2
 *
 * - ADDR1 : 1;
 * - ADDR0 : 0;
 */
#define IRTHERMO2_I2C_ADDRESS_2                                 0x44

/**
 * I2C address 3
 *
 * - ADDR1 : 1;
 * - ADDR0 : 1;
 */
#define IRTHERMO2_I2C_ADDRESS_3                                 0x45
/** \} */

/**
 * \defgroup reg_addr Register Address
 * \{
 */
#define IRTHERMO2_SENSOR_VOLTAGE                                0x00
#define IRTHERMO2_LOCAL_TEMPERATURE                             0x01
#define IRTHERMO2_CONFIGURATION                                 0x02
#define IRTHERMO2_OBJECT_TEMPERATURE                            0x03
#define IRTHERMO2_STATUS                                        0x04
#define IRTHERMO2_STATUS_MASK_AND_ENABLE                        0x05
#define IRTHERMO2_OBJECT_HIGH_LIMIT_TEMP                        0x06
#define IRTHERMO2_OBJECT_LOW_LIMIT_TEMP                         0x07
#define IRTHERMO2_LOCAL_HIGH_LIMIT_TEMP                         0x08
#define IRTHERMO2_LOCAL_LOW_LIMIT_TEMP                          0x09
#define IRTHERMO2_S0_COEFFICIENT                                0x0A
#define IRTHERMO2_A0_COEFFICIENT                                0x0B
#define IRTHERMO2_A1_COEFFICIENT                                0x0C
#define IRTHERMO2_B0_COEFFICIENT                                0x0D
#define IRTHERMO2_B1_COEFFICIENT                                0x0E
#define IRTHERMO2_B2_COEFFICIENT                                0x0F
#define IRTHERMO2_C_COEFFICIENT                                 0x10
#define IRTHERMO2_TC0_COEFFICIENT                               0X11
#define IRTHERMO2_TC1_COEFFICIENT                               0x12
#define IRTHERMO2_DEVICE_ID                                     0x1F
#define IRTHERMO2_MEMORY_ACCESS                                 0x2A
/** \} */

/**
 * \defgroup command Command
 * \{
 */
#define IRTHERMO2_RESULT_OK                                     1
#define IRTHERMO2_RESULT_ERROR                                  0
#define IRTHERMO2_CFG_MODEON                                    0x1000
#define IRTHERMO2_CFG_RESET                                     0x8000
#define IRTHERMO2_CFG_1SAMPLE                                   0x0000
#define IRTHERMO2_CFG_2SAMPLE                                   0x0200
#define IRTHERMO2_CFG_4SAMPLE                                   0x0400
#define IRTHERMO2_CFG_8SAMPLE                                   0x0600
#define IRTHERMO2_CFG_16SAMPLE                                  0x0800
#define IRTHERMO2_CFG_ALERTEN                                   0x0100
#define IRTHERMO2_CFG_ALERTF                                    0x0080
#define IRTHERMO2_CFG_TRANSC                                    0x0040
#define IRTHERMO2_STAT_ALERTEN                                  0x8000
#define IRTHERMO2_STAT_CRTEN                                    0x4000
#define IRTHERMO2_DEVICE_ID_VALUE                               0x0078
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

    digital_in_t al;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} irthermo2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t al;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} irthermo2_cfg_t;

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
void irthermo2_cfg_setup ( irthermo2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg        Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IRTHERMO2_RETVAL irthermo2_init ( irthermo2_t *ctx, irthermo2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 *
 * @description This function executes default configuration for IrThermo2 click.
 */
void irthermo2_default_cfg ( irthermo2_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void irthermo2_generic_write ( irthermo2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void irthermo2_generic_read ( irthermo2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write 16-bit data function
 *
 * @param ctx                        Click object.
 * @param address                    8-bit register address.
 * @param write_command              16-bit data to write to given address.
 *
 * @description Function write 16-bit data to given 8-bit register address.
 */
void irthermo2_write_data ( irthermo2_t *ctx, uint8_t address, uint16_t write_data );

/**
 * @brief Generic read 16-bit data from 8-bit address function
 *
 * @param ctx                        Click object.
 * @param address                    8-bit register address.
 *
 * @returns result                   16-bit data from given address
 *
 * @description Function read 16-bit data from given 8-bit register address.
 */
uint16_t irthermo2_read_data ( irthermo2_t *ctx, uint8_t address );

/**
 * @brief Check device ID function
 *
 * @param ctx                        Click object.
 *
 * @returns result (8-bit value): 1 - ID value OK; 0 - ID value ERROR;
 *
 * @description Function check device ID and return ERROR ( 0 ) or OK ( 1 ).
 */
uint8_t irthermo2_check_id ( irthermo2_t *ctx );

/**
 * @brief Get object temperature in degrees Celsius function
 *
 * @param ctx                        Click object.
 *
 * @returns result                   Float temperature data.
 *
 * @description Function read 16-bit data from object temperature register and
 * calculate temperature in degrees Celsius.
 *
 * @note Full scale allows a result of up to � 256�C
 */
float irthermo2_get_object_temperature_c ( irthermo2_t *ctx );

/**
 * @brief Get object temperature in degrees Fahrenheit function
 *
 * @param ctx                        Click object.
 *
 * @returns result                   Float temperature data
 *
 * @description Function read 16-bit data from object temperature register and
 * calculate temperature in degrees Fahrenheit.
 */
float irthermo2_get_object_temperature_f ( irthermo2_t *ctx );

/**
 * @brief Get raw temperature in degrees Celsius function
 *
 * @param ctx                        Click object.
 *
 * @returns result                   Float temperature data
 *
 * @description Function read 16-bit data from raw temperature register and
 * calculate temperature in degrees Celsius.
 *
 * @note Full scale allows a result of up to � 256�C
 */
float irthermo2_get_raw_temperature ( irthermo2_t *ctx );

/**
 * @brief Get state of alert function
 *
 * @param ctx                        Click object.
 *
 * @returns result  (state of INT pin) :  0 - ACTIVE; 1 - NO ACTIVE
 *
 * @description Function get state of alert - INT pin of TMP007 sesnor on IrThermo 2 Click.
 */
uint8_t irhhermo2_get_alert ( irthermo2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _IRTHERMO2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

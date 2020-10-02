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
 * \brief This file contains API for Temp-Log Click driver.
 *
 * \addtogroup templog Temp-Log Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPLOG_H
#define TEMPLOG_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define TEMPLOG_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.alt = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPLOG_RETVAL  uint8_t

#define TEMPLOG_OK           0x00
#define TEMPLOG_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup temperature_macros Temperature Macros
 * \{
 */
#define TEMP_LOG_TEMPERATURE                  0x00
#define TEMP_LOG_CONFIGURATION                0x01
#define TEMP_LOG_TLOW_LIMIT                   0x02
#define TEMP_LOG_THIGH_LIMIT                  0x03
#define TEMP_LOG_CONFIGURATION_NONVOL         0x11
#define TEMP_LOG_TLOW_LIMIT_NONVOL            0x12
#define TEMP_LOG_THIGH_LIMIT_NONVOL           0x13
#define TEMP_LOG_SLAVE_ADDRESS                0x48
#define TEMP_LOG_8_BITS_DATA                  0x01
#define TEMP_LOG_16_BITS_DATA                 0x00
#define TEMP_LOG_RESOLUTION_9_BITS            0x0000
#define TEMP_LOG_RESOLUTION_10_BITS           0x2000
#define TEMP_LOG_RESOLUTION_11_BITS           0x4000
#define TEMP_LOG_RESOLUTION_12_BITS           0x6000
#define TEMP_LOG_0_CELSIUS                    0x0000
#define TEMP_LOG_10_125_CELSIUS               0x0A20
#define TEMP_LOG_25_25_CELSIUS                0x1940
#define TEMP_LOG_50_5_CELSIUS                 0x3200
#define TEMP_LOG_75_CELSIUS                   0x4B00
#define TEMP_LOG_100_CELSIUS                  0x6400
#define TEMP_LOG_125_CELSIUS                  0x7D00
#define TEMP_LOG_NEGATIVE_10_125_CELSIUS      0xF5E0
#define TEMP_LOG_NEGATIVE_25_25_CELSIUS       0xE7C0
#define TEMP_LOG_NEGATIVE_50_5_CELSIUS        0xCE80
#define TEMP_LOG_NEGATIVE_55_CELSIUS          0xC900
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
  
    digital_in_t alt;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;

} templog_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t alt;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;

} templog_cfg_t;

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
void templog_cfg_setup ( templog_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @returns Macro describing if init was successful
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPLOG_RETVAL templog_init ( templog_t *ctx, templog_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Temp&Log click.
 */
void templog_default_cfg ( templog_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx               Click object.
 * @param reg               Register address.
 * @param transfer_data     Data buf to be written.
 * @param len               Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void templog_generic_write ( templog_t *ctx, uint8_t reg, uint16_t transfer_data, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @returns            Read value.
 *
 * @description This function reads data from the desired register.
 */
uint16_t templog_generic_read ( templog_t *ctx, uint8_t reg );

/**
 * @brief Temp read function.
 *
 * @param ctx          Click object.
 * @param resolution   Resolution.
 *
 * @returns            Read value.
 *
 * @description This function reads decimal value of temp.
 */
uint16_t temp_log_read_temp_dec ( templog_t *ctx, uint16_t resolution );

/**
 * @brief Convert function.
 *
 * @param temperature_data          Data to be converted.
 *
 * @returns                         Converted value.
 *
 * @description This function converts temperature data to celsius value.
 */
float temp_log_convert_to_celsius ( uint16_t temperature_data );

/**
 * @brief Alert function.
 *
 * @param ctx          Click object.
 *
 * @returns            Value describing if temp is alarming.
 *
 * @description This function alerts user if temperature limit is alarming.
 */
uint8_t temp_log_get_alert ( templog_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPLOG_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

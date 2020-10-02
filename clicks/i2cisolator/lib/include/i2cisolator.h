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
 * \brief This file contains API for I2C isolator Click driver.
 *
 * \addtogroup i2cisolator I2C isolator Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef I2CISOLATOR_H
#define I2CISOLATOR_H

#include "drv_digital_out.h"
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
#define I2CISOLATOR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define I2CISOLATOR_RETVAL  uint8_t

#define I2CISOLATOR_OK           0x00
#define I2CISOLATOR_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup Command commands
 * \{
 */
#define I2CISOLATOR_IRTHERMO2_RESULT_OK                                         1
#define I2CISOLATOR_IRTHERMO2_RESULT_ERROR                                      0
/** \} */

/** \} */ // End group macro 
// -------------------------------------------------------------- PRIVATE MACROS 
/**
 * \defgroup macros Macros
 * \{
 */
/**
 * \defgroup register_address Register Address
 * \{
 */
/* Register Address */
#define I2CISOLATOR_IRTHERMO2_SENSOR_VOLTAGE                                   0x00
#define I2CISOLATOR_IRTHERMO2_LOCAL_TEMPERATURE                                0x01
#define I2CISOLATOR_IRTHERMO2_CONFIGURATION                                    0x02
#define I2CISOLATOR_IRTHERMO2_OBJECT_TEMPERATURE                               0x03
#define I2CISOLATOR_IRTHERMO2_STATUS                                           0x04
#define I2CISOLATOR_IRTHERMO2_STATUS_MASK_AND_ENABLE                           0x05
#define I2CISOLATOR_IRTHERMO2_OBJECT_HIGH_LIMIT_TEMP                           0x06
#define I2CISOLATOR_IRTHERMO2_OBJECT_LOW_LIMIT_TEMP                            0x07
#define I2CISOLATOR_IRTHERMO2_LOCAL_HIGH_LIMIT_TEMP                            0x08
#define I2CISOLATOR_IRTHERMO2_LOCAL_LOW_LIMIT_TEMP                             0x09
#define I2CISOLATOR_IRTHERMO2_S0_COEFFICIENT                                   0x0A
#define I2CISOLATOR_IRTHERMO2_A0_COEFFICIENT                                   0x0B
#define I2CISOLATOR_IRTHERMO2_A1_COEFFICIENT                                   0x0C
#define I2CISOLATOR_IRTHERMO2_B0_COEFFICIENT                                   0x0D
#define I2CISOLATOR_IRTHERMO2_B1_COEFFICIENT                                   0x0E
#define I2CISOLATOR_IRTHERMO2_B2_COEFFICIENT                                   0x0F
#define I2CISOLATOR_IRTHERMO2_C_COEFFICIENT                                    0x10
#define I2CISOLATOR_IRTHERMO2_TC0_COEFFICIENT                                  0X11
#define I2CISOLATOR_IRTHERMO2_TC1_COEFFICIENT                                  0x12
#define I2CISOLATOR_IRTHERMO2_DEVICE_ID                                        0x1F
#define I2CISOLATOR_IRTHERMO2_MEMORY_ACCESS                                    0x2A
/** \} */

/**
 * \defgroup Command commands
 * \{
 */
#define I2CISOLATOR_IRTHERMO2_CFG_MODEON                                       0x1000
#define I2CISOLATOR_IRTHERMO2_CFG_RESET                                        0x8000
#define I2CISOLATOR_IRTHERMO2_CFG_1SAMPLE                                      0x0000
#define I2CISOLATOR_IRTHERMO2_CFG_2SAMPLE                                      0x0200
#define I2CISOLATOR_IRTHERMO2_CFG_4SAMPLE                                      0x0400
#define I2CISOLATOR_IRTHERMO2_CFG_8SAMPLE                                      0x0600
#define I2CISOLATOR_IRTHERMO2_CFG_16SAMPLE                                     0x0800
#define I2CISOLATOR_IRTHERMO2_CFG_ALERTEN                                      0x0100
#define I2CISOLATOR_IRTHERMO2_CFG_ALERTF                                       0x0080
#define I2CISOLATOR_IRTHERMO2_CFG_TRANSC                                       0x0040
#define I2CISOLATOR_IRTHERMO2_STAT_ALERTEN                                     0x8000
#define I2CISOLATOR_IRTHERMO2_STAT_CRTEN                                       0x4000
#define I2CISOLATOR_IRTHERMO2_DEVICE_ID_VALUE                                  0x0078
/** \} */

/**
 * \defgroup register_i2c_address Register I2C Address
 * \{
 */
#define I2CISOLATOR_IRTHERMO2_I2C_ADDRESS_0                                    0x40
#define I2CISOLATOR_IRTHERMO2_I2C_ADDRESS_1                                    0x41
#define I2CISOLATOR_IRTHERMO2_I2C_ADDRESS_2                                    0x44
#define I2CISOLATOR_IRTHERMO2_I2C_ADDRESS_3                                    0x45
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
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} i2cisolator_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
  
    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} i2cisolator_cfg_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 

/** \} */ // End constants group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group
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
void i2cisolator_cfg_setup ( i2cisolator_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param i2cisolator Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
I2CISOLATOR_RETVAL i2cisolator_init ( i2cisolator_t *ctx, i2cisolator_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for I2Cisolator click.
 */
void i2cisolator_default_cfg ( i2cisolator_t *ctx );

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
void i2cisolator_generic_write ( i2cisolator_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void i2cisolator_generic_read ( i2cisolator_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif  // _I2CISOLATOR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

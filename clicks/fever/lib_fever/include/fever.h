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
 * \brief This file contains API for Fever Click driver.
 *
 * \addtogroup fever Fever Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FEVER_H
#define FEVER_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define FEVER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );\
  cfg.os   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FEVER_RETVAL  uint8_t

#define FEVER_OK           0x00
#define FEVER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers  Registers
 * \{
 */
#define FEVER_TEMP                         0x00
#define FEVER_CONFIG                       0x01
#define FEVER_THYST                        0x02
#define FEVER_TOS                          0x03
/** \} */

/**
 * \defgroup config_commands  Config commands
 * \{
 */
#define FEVER_SHUTDOWN                     0x01
#define FEVER_POWERUP                      0xFE
#define FEVER_INTERUPT_MODE                0x02
#define FEVER_COMPARATOR_MODE              0xFD
/** \} */

/**
 * \defgroup set_active_signal  Set active signal
 * \{
 */
#define FEVER_OS_ACTIVE_HIGH               0x04
#define FEVER_OS_ACTIVE_LOW                0xFB
/** \} */

/**
 * \defgroup length_of_fault_queue  Length of faul queue
 * \{
 */
#define FEVER_FAULT_QUEUE_1                0xE7
#define FEVER_FAULT_QUEUE_2                0x08
#define FEVER_FAULT_QUEUE_4                0x10
#define FEVER_FAULT_QUEUE_6                0x18
/** \} */

/**
 * \defgroup data_format  Data format
 * \{
 */
#define FEVER_EXTENDED_DATA_FORMAT         0x20
#define FEVER_NORMAL_DATA_FORMAT           0xDF
/** \} */

/**
 * \defgroup i2c_timeout  I2C Timeout
 * \{
 */
#define FEVER_TIMEOUT_DISABLE              0x40
#define FEVER_TIMEOUT_ENABLE               0xBF
/** \} */

/**
 * \defgroup measure  Measure
 * \{
 */
#define FEVER_ONE_SHOT_MEASURE             0x80
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

    digital_in_t os;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} fever_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t os;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} fever_cfg_t;

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
void fever_cfg_setup ( fever_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
FEVER_RETVAL fever_init ( fever_t *ctx, fever_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Fever click.
 */
void fever_default_cfg ( fever_t *ctx );

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
void fever_generic_write ( fever_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void fever_generic_read ( fever_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get temperature 
 * 
 * @param ctx          Click object.
 *
 * @return return temperature value in Celsius.
 */
float fever_get_temperature ( fever_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _FEVER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

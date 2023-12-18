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
 * \brief This file contains API for Buck 11 Click driver.
 *
 * \addtogroup buck11 Buck 11 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK11_H
#define BUCK11_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define BUCK11_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK11_RETVAL  uint8_t

#define BUCK11_OK           0x00
#define BUCK11_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup  device_dlave_address  Device Slave Address
 * \{
 */
#define BUCK11_MCP3221A5T_DEV_ADDR        0x4D
/** \} */

/**
 * \defgroup vout_results_resolution VOUT results resolution
 * \{
 */
#define BUCK11_VOUT_VOLTS                 0x00
#define BUCK11_VOUT_MILLIVOLTS            0x01
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

} buck11_t;

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

} buck11_cfg_t;

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
void buck11_cfg_setup ( buck11_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buck11 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCK11_RETVAL buck11_init ( buck11_t *ctx, buck11_cfg_t *cfg );

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
void buck11_generic_write ( buck11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void buck11_generic_read ( buck11_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set VDD Value function
 *
 * 
 * @param vdd_volts    The desired VDD value in Volts to be set
 *
 * @description This function allows user to set VDD voltage to the desired (measured) value.
 * @note This voltage is used as reference voltage for the MCP3221A5T converter.
 */
void buck11_set_vdd_value ( float vdd_volts );

/**
 * @brief ADC Read function
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function reads the results of the AD conversion from the MCP3221A5T 12-bit converter.
 */
uint16_t buck11_read_adc ( buck11_t *ctx );

/**
 * @brief Get VOUT function
 *
 * 
 * @param ctx               Click object.
 * @param vout_resolution   0 - To get VOUT value in volts, 
 *                          1 (or other value different from 0) - To get VOUT value in millivolts
 *
 * @description This function allows user to get VOUT voltage value in the desired unit resolution, volts or millivolts.
 * @note This voltage is a result of one conversion cycle
 */
float buck11_get_vout ( buck11_t *ctx, uint8_t vout_resolution );

/**
 * @brief Get Averaged VOUT function
 *
 *
 * @param ctx               Click object.
 * @param vout_resolution   0 - To get VOUT value in volts,
 *                          1 (or other value different from 0) - To get VOUT value in millivolts
 * @param n_samples         Number of samples to be performed for one measurement cycle
 *
 * @description This function allows user to get the averaged VOUT voltage value in the desired unit resolution, volts or millivolts.
 * @note The number of conversions for one measurement cycle is selectable.
 */
float buck11_get_averaged_vout ( buck11_t *ctx, uint8_t vout_resolution, uint8_t n_samples );


#ifdef __cplusplus
}
#endif
#endif  // _BUCK11_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

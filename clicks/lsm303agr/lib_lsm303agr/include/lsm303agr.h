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
 * \brief This file contains API for LSM303AGR Click driver.
 *
 * \addtogroup lsm303agr LSM303AGR Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LSM303AGR_H
#define LSM303AGR_H

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
#define LSM303AGR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LSM303AGR_RETVAL  uint8_t

#define LSM303AGR_OK           0x00
#define LSM303AGR_INIT_ERROR   0xFF
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

    uint8_t slave_address;

} lsm303agr_t;

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
    uint8_t i2c_address;

} lsm303agr_cfg_t;

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
void lsm303agr_cfg_setup ( lsm303agr_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param lsm303agr Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LSM303AGR_RETVAL lsm303agr_init ( lsm303agr_t *ctx, lsm303agr_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for LSM303AGR click.
 */
void lsm303agr_default_cfg ( lsm303agr_t *ctx );


/**
 * @brief Generic read data function.
 *
 * @param lightranger       Click object.
 * @param reg_addr          Register address.
 * @param read_buf          Read buffer.
 * @param read_len          Buffer length.
 *
 * @description This function reads 16-bit data from given address.
 */
void lsm303agr_read_data ( lsm303agr_t* ctx, uint8_t reg_addr, uint8_t *read_buf, uint8_t read_len );

/**
 * @brief Generic write data function.
 *
 * @param lsm303agr       Click object.
 * @param reg_addr        Register address.
 * @param write_buf       Read buffer.
 * @param write_len       Buffer length.
 *
 *
 * @description This function writes 16-bit command to given address.
 */
void lsm303agr_write_data ( lsm303agr_t* ctx, uint8_t reg_addr, uint8_t *write_buf, uint8_t write_len );


/**
 * @brief Reading the raw X axis data and calculating the value :
 *
 * @param ctx  Click object.
 *
 * @returns Returns X axis accel data 
 * 
 */
float lsm303agr_get_acc_axis_x ( lsm303agr_t *ctx );

/**
 * @brief Reading the raw Y axis data and calculating the value :
 *
 *
 * @param ctx  Click object.
 *
 * @returns Returns Y axis accel data
 */
float lsm303agr_get_acc_axis_y ( lsm303agr_t *ctx );

/**
 * @brief Reading the raw Z axis data and calculating the value :
 *
 *
 * @param ctx  Click object.
 *
 * @returns Returns Z axis accel data
 * 
 */
float lsm303agr_get_acc_axis_z ( lsm303agr_t *ctx );

/**
 * @brief Reading the raw X axis data and calculating the value :
 *
 *
 * @param ctx  Click object.
 *
 * @returns Returns raw X axis from the magnetometer.
 * 
 */
float lsm303agr_get_mag_axis_x ( lsm303agr_t *ctx );

/**
 * @brief Reading the raw Y axis data and calculating the value :
 *
 *
 * @param ctx  Click object.
 *
 * @returns Returns raw Y axis from the magnetometer.
 * 
 */
float lsm303agr_get_mag_axis_y ( lsm303agr_t *ctx );

/**
 * @brief Reading the raw Z axis data and calculating the value :
 *
 *
 * @param ctx  Click object.
 *
 * @returns Returns raw Z axis from the magnetometer.
 * 
 */
float lsm303agr_get_mag_axis_z (  lsm303agr_t *ctx );

/**
 * @brief Accelerometer init
 *
 * @param ctx  Click object.
 *
 * @note  
 * <pre>
 * Sets accelerometer operating mode to HR / Normal / Low-power mode (100 Hz) 
 * by writing  0x57h in 0x20h address
 * </pre>
 */
void lsm303agr_accelerometer_init ( lsm303agr_t *ctx );

/**
 * @brief Magnetometer init
 *
 * @param ctx  Click object.
 *
 * @note
 *<pre> Sets magnetoometer operating mode to Continuous mode / ODR 10 Hz 
 *  by writing  0x00h in 0x60h address
 *</pre>
 */
void lsm303agr_magnetometer_init ( lsm303agr_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _LSM303AGR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for Surface temp Click driver.
 *
 * \addtogroup surfacetemp Surface temp Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SURFACETEMP_H
#define SURFACETEMP_H

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
#define SURFACETEMP_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SURFACETEMP_RETVAL  uint8_t

#define SURFACETEMP_OK           0x00
#define SURFACETEMP_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_status Device status
 * \{
 */
#define DEVICE_OK    0
#define DEVICE_ERROR 1
/** \} */

/**
 * \defgroup device_address Device address
 * \{
 */
#define SURFACETEMP_SLAVE_DEVICE_ADDR_0_0   0x48
#define SURFACETEMP_SLAVE_DEVICE_ADDR_0_1   0x49
#define SURFACETEMP_SLAVE_DEVICE_ADDR_1_0   0x4A
#define SURFACETEMP_SLAVE_DEVICE_ADDR_1_1   0x4B
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define SURFACETEMP_REG_TEMP_MSB         0x00
#define SURFACETEMP_REG_TEMP_LSB         0x01
#define SURFACETEMP_REG_STATUS           0x02
#define SURFACETEMP_REG_CONFIG           0x03
#define SURFACETEMP_REG_T_HIGH_SETP_MSB  0x04
#define SURFACETEMP_REG_T_HIGH_SETP_LSB  0x05
#define SURFACETEMP_REG_T_LOW_SETP_MSB   0x06
#define SURFACETEMP_REG_T_LOW_SETP_LSB   0x07
#define SURFACETEMP_REG_T_CRIT_SETP_MSB  0x08
#define SURFACETEMP_REG_T_CRIT_SETP_LSB  0x09
#define SURFACETEMP_REG_T_HYST_SETP      0x0A
#define SURFACETEMP_REG_ID               0x0B
#define SURFACETEMP_REG_SOFT_RESET       0x2F
/** \} */

/**
 * \defgroup reg_mask  Reg Mask
 * \{
 */
#define SURFACETEMP_T_LOW_MASK           0x10
#define SURFACETEMP_T_HIGH_MASK          0x20
#define SURFACETEMP_T_CRIT_MASK          0x40
#define SURFACETEMP_RDY_MASK             0x80
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
    // Output pins 

    digital_out_t rst;
    digital_out_t pwm;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} surfacetemp_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t pwm;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} surfacetemp_cfg_t;

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
void surfacetemp_cfg_setup ( surfacetemp_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SURFACETEMP_RETVAL surfacetemp_init ( surfacetemp_t *ctx, surfacetemp_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for SurfaceTemp click.
 */
void surfacetemp_default_cfg ( surfacetemp_t *ctx );

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
void surfacetemp_generic_write ( surfacetemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void surfacetemp_generic_read ( surfacetemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Getting PWM pin state
 *
 * @param ctx  Click object.
 * 
 * @returns 0 if PWM pin is LOW
 * @returns 1 if PWM pin is HIGH
 *
 * @note This function returns PWM pin state
 */
uint8_t surfacetemp_get_pwm_pin ( surfacetemp_t *ctx );

/**
 * @brief Soft reset
 *
 * @param ctx  Click object.
 * 
 * @note This function issues soft reset command
 */
void surfacetemp_soft_reset ( surfacetemp_t *ctx );

/**
 * @brief Getting temperature value
 *
 * @param ctx  Click object.
 * 
 * @returns Temperature value
 *
 * @note This function reads temperature registers and calculates temperature value
 */
float surfacetemp_get_temperature ( surfacetemp_t *ctx );

/**
 * @brief Getting device status
 *
 * @param ctx  Click object.
 * 
 * @returns Status register value
 *
 * @note This function returns status register value
 */
uint8_t surfacetemp_get_status ( surfacetemp_t *ctx );

/**
 * @brief Setting high threshold limit
 *
 * @param ctx  Click object.
 * @param high_threshold - high threshold value
 *
 * @returns 0 for valid high threshold value (i.e. if threshold value is between -40 and 150)
 * @returns 1 for invalid high threshold value (i.e. if threshold value is not between -40 and 150)
 *
 * @note This function sets high threshold value
 */
uint8_t surfacetemp_set_high_threshold ( surfacetemp_t *ctx, float high_threshold );

/**
 * @brief Setting low threshold limit
 *
 * @param ctx  Click object.
 * @param low_threshold - low threshold value
 *
 * @returns 0 for valid low threshold value (i.e. if threshold value is between -40 and 150)
 * @returns 1 for invalid low threshold value (i.e. if threshold value is not between -40 and 150)
 *
 * @note This function sets low threshold value
 */
uint8_t surfacetemp_set_low_threshold ( surfacetemp_t *ctx, float high_threshold );

/**
 * @brief Setting critical threshold limit
 *
 * @param ctx  Click object.
 * @param critical_threshold - critical threshold value
 *
 * @returns 0 for valid critical threshold value (i.e. if threshold value is between -40 and 150)
 * @returns 1 for invalid critical threshold value (i.e. if threshold value is not between -40 and 150)
 *
 * @note This function sets critical threshold value
 */
uint8_t surfacetemp_set_critical_threshold ( surfacetemp_t *ctx, float high_threshold );

/**
 * @brief Setting hysteresis value
 *
 * @param ctx  Click object.
 * @param hysteresis - hysteresis value
 *
 * @returns 0 for valid hysteresis value (i.e. if hysteresis value is between 0 and 15)
 * @returns 1 for invalid hysteresis value (i.e. if hysteresis value is not between 0 and 15)
 *
 * @note This function sets high threshold value
 */
uint8_t surfacetemp_set_hysteresis ( surfacetemp_t *ctx, uint8_t hysteresis );

/**
 * @brief Device initialization
 *
 * @param ctx  Click object.
 * 
 * @returns 0 for successful initialization (i.e. if device ID is correct)
 * @returns 1 for unsuccessful initialization (i.e. if device ID is incorrect)
 *
 * @note This function issues soft reset command
 * @note This function gets device ID
 * @note This function sets resolution to 16-bit
 * @note This function sets continious conversion mode
 * @note This function sets comprator mode
 * @note This function sets INT and CT(CS) pins to active low
 * @note This function sets fault queue to 4 faults
 */
uint8_t surfacetemp_setup ( surfacetemp_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _SURFACETEMP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

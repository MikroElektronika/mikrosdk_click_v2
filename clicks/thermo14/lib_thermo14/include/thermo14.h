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
 * \brief This file contains API for Thermo 14 Click driver.
 *
 * \addtogroup thermo14 Thermo 14 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO14_H
#define THERMO14_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define THERMO14_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO14_RETVAL  uint8_t

#define THERMO14_OK           0x00
#define THERMO14_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup ARA and I2C Device Address
 * \{
 */
#define THERMO14_I2C_ADR_VDD          0x38
#define THERMO14_I2C_ADR_GND          0x3F
#define THERMO14_ARA_ADR              0x0C
/** \} */

/**
 * \defgroup registar_map   Register Map
 * \{
 */
#define THERMO14_WHOAMI               0x01
#define THERMO14_TEMP_H_LIMIT         0x02
#define THERMO14_TEMP_L_LIMIT         0x03
#define THERMO14_CTL                  0x04
#define THERMO14_STAT                 0x05
#define THERMO14_TEMP_L_OUT           0x06
#define THERMO14_TEMP_H_OUT           0x07
#define THERMO14_SW_RST               0x0C
/** \} */

/**
 * \defgroup control_registar   Control Register
 * \{
 */
#define THERMO14_CTL_LOW_ODR_ST       0x80
#define THERMO14_CTL_BDU              0x40
#define THERMO14_CTL_AVG_8            0x00
#define THERMO14_CTL_AVG_4            0x10
#define THERMO14_CTL_AVG_2            0x20
#define THERMO14_CTL_AVG_1            0x30
#define THERMO14_CTL_IF_ADR_INC       0x08
#define THERMO14_CTL_FREERUN          0x04
#define THERMO14_CTL_TIME_OUT_DIS     0x02
#define THERMO14_CTL_ONE_SHOT         0x01
/** \} */

/**
 * \defgroup control_registar   Control Register
 * \{
 */
#define THERMO14_SW_RST_RST_CMD       0x02
#define THERMO14_SW_RST_LOW_ODR_EN    0x40
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

} thermo14_t;

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

} thermo14_cfg_t;

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
void thermo14_cfg_setup ( thermo14_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMO14_RETVAL thermo14_init ( thermo14_t *ctx, thermo14_cfg_t *cfg );

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
void thermo14_generic_write ( thermo14_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void thermo14_generic_read ( thermo14_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

void thermo14_default_cfg ( thermo14_t *ctx );

/**
 * @brief Reset function.
 *
 * @param ctx          Click object.
 * 
 * @description This function is used to perform software reset.
**/
void thermo14_reset ( thermo14_t *ctx );

/**
 * @brief Sensor enable function.
 *
 * @param ctx          Click object.
 * 
 * @description This function is used to enable sensor.
**/
void thermo14_sensor_enable ( thermo14_t *ctx );

/**
 * @brief Get Raw Temperature Data function.
 *
 * @param ctx          Click object.
 * 
 * @returns temp_raw 16-bit signed data that defines the raw value
 *
 * @description This function is used to get the raw value.
**/
int16_t thermo14_temp_raw_get ( thermo14_t *ctx );

/**
 * @brief Temperature Calculation function.     ````````````````  
 * 
 *
 * @param ctx          Click object.
 * @param temp_raw  16-bit signed data that defines the raw value
 *
 * @returns float value that defines temperature value.
 *
 * @description This function is used to perform necessary calculacion in order to get temperature freom raw data.
**/
float thermo14_raw_to_celsius ( thermo14_t *ctx, int16_t temp_raw );

/**
 * @brief Get Temperature in Centigrade function
 *
 * @param ctx          Click object.
 * 
 * @returns float value that defines temperature value
 *
 * @description This function is used to get the temperature.
**/
float thermo14_get_temperature ( thermo14_t *ctx );

/**
 * @brief Get Interrupt state function
 *
 * @param ctx          Click object.
 * 
 * @return
 * - 0 : Interrupt has not occured
 * - 1 : Interrupt has occured
 *
 * @description This function is used to check if an interrupt has occured.
**/
uint8_t thermo14_get_int ( thermo14_t *ctx );

/**
 * @brief Set the low temperature threshold value function
 *
 * @param ctx          Click object.
 * @param trsh_val  low temperature threshold value
 *
 * @description This function is used to set the low temperature threshold value.
**/
void thermo14_low_temp_trsh ( thermo14_t *ctx, float trsh_val );

/**
 * @brief Set the high temperature threshold value function
 *
 * @param ctx          Click object.
 * @param trsh_val  high temperature threshold value
 *
 * @description This function is used to set the high temperature threshold value.
**/
void thermo14_high_temp_trsh ( thermo14_t *ctx, float trsh_val );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO14_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for Ambient 5 Click driver.
 *
 * \addtogroup ambient5 Ambient 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AMBIENT5_H
#define AMBIENT5_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define AMBIENT5_DEVICE_ADDRESS                         0x10
 /** \} */ // End group slave_addr

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define AMBIENT5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMBIENT5_RETVAL  uint8_t

#define AMBIENT5_OK           0x00
#define AMBIENT5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define AMBIENT5_CONFIGURATION                          0x00
#define AMBIENT5_HIGH_THRESHOLD                         0x01
#define AMBIENT5_LOW_THRESHOLD                          0x02
#define AMBIENT5_POWER_SAVING_MODE                      0x03
#define AMBIENT5_HIGH_RESOLUTION_OUTPUT_DATA            0x04
#define AMBIENT5_WHITE_CHANNEL_OUTPUT_DATA              0x05
#define AMBIENT5_INTERRUPT_STATUS                       0x06
 /** \} */ // End group register

/**
 * \defgroup configuration_register Configuration register
 * \{
 */
#define AMBIENT5_GAIN_x1                                0x0000
#define AMBIENT5_GAIN_x2                                0x0800
#define AMBIENT5_GAIN_x1_8                              0x1000
#define AMBIENT5_GAIN_x1_4                              0x1800
#define AMBIENT5_INTEGRATION_TIME_25ms                  0x0300
#define AMBIENT5_INTEGRATION_TIME_50ms                  0x0200
#define AMBIENT5_INTEGRATION_TIME_100ms                 0x0000
#define AMBIENT5_INTEGRATION_TIME_200ms                 0x0040
#define AMBIENT5_INTEGRATION_TIME_400ms                 0x0080
#define AMBIENT5_INTEGRATION_TIME_800ms                 0x00C0
#define AMBIENT5_PERSISTANCE_PROTECT_NUMBER_1           0x0000
#define AMBIENT5_PERSISTANCE_PROTECT_NUMBER_2           0x0010
#define AMBIENT5_PERSISTANCE_PROTECT_NUMBER_4           0x0020
#define AMBIENT5_PERSISTANCE_PROTECT_NUMBER_8           0x0030
#define AMBIENT5_INTERRUPT_DISABLE                      0x0000
#define AMBIENT5_INTERRUPT_ENABLE                       0x0002
#define AMBIENT5_POWER_ON                               0x0000
#define AMBIENT5_SHUT_DOWN                              0x0001
 /** \} */ // End group configuration_register

/**
 * \defgroup power_saving_mode Power saving mode
 * \{
 */
#define AMBIENT5_MODE_1                                 0x0000
#define AMBIENT5_MODE_2                                 0x0002
#define AMBIENT5_MODE_3                                 0x0004
#define AMBIENT5_MODE_4                                 0x0006
#define AMBIENT5_POWER_SAVING_MODE_DISABLE              0x0000
#define AMBIENT5_POWER_SAVING_MODE_ENABLE               0x0001
 /** \} */ // End group power_saving_mode



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

} ambient5_t;

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

} ambient5_cfg_t;

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
 * @description This function initializes click configuration structure
 * to init state.
 * @note All used pins will be set to unconnected state.
 */
void ambient5_cfg_setup ( ambient5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals
 * used for this click.
 */
AMBIENT5_RETVAL ambient5_init ( ambient5_t *ctx, ambient5_cfg_t *cfg );

/**
 * @brief Default configuration function.
 * @param ambient5 Click object.
 * 
 * @description This function sets default configuration for the module.
 */
void ambient5_default_cfg ( ambient5_t *ctx );

/**
 * @brief Set register function.
 *
 * @param ctx          Click object.
 * @param reg_addr          Register address.
 * @param reg_value     Register value to be written.
 * @description This function writes register value to the desired register.
 */
void ambient5_set_register ( ambient5_t* ctx, uint8_t reg_addr,
	                         uint16_t reg_value );

/**
 * @brief Get register function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads data from the desired register.
 */
int16_t ambient5_get_register ( ambient5_t* ctx, uint8_t reg );

/**
 * @brief Get resolution
 *
 * @param ctx          Click object.
 *
 * @description This function calculates resolution of output data in 
 * "high resolution" and "white channel" registers.
 */
float ambient5_get_resolution ( ambient5_t* ctx );

/**
 * @brief Get refresh time.
 *
 * @param ctx          Click object.
 *
 * @returns            Refresh time.
 *
 * @description This function calculates refresh time, based on user settings
 * for integration time and power saving mode.
 */
uint16_t ambient5_get_refresh_time ( ambient5_t* ctx );

/**
 * @brief Get high resolution light level.
 *
 * @param ctx          Click object.
 *
 * @returns            Light level.
 *
 * @description This function calculates light level (lux) read from
 * "high resolution output data" register.
 */
float ambient5_get_high_resolution_light_level ( ambient5_t* ctx );

/**
 * @brief Get white channel light level.
 *
 * @param ctx          Click object.
 *
 * @returns            Light level.
 *
 * @description This function calculates light level (lux) read from
 * "white channel output data" register.
 */
float ambient5_get_white_channel_light_level ( ambient5_t* ctx );

/**
 * @brief Set low light level threshold.
 *
 * @param ctx                        Click object.
 * @param low_light_level_threshold  Low light level threshold.
 *
 * @description This function calculates light level (lux) read from 
 * "white channel output data" register.
 */
void ambient5_set_low_light_level_threshold ( ambient5_t* ctx,
	                                          float low_light_level_threshold );

/**
 * @brief Set high light level threshold.
 *
 * @param ctx                         Click object.
 * @param high_light_level_threshold  High light level threshold.
 *
 * @description This function sets high light level threshold (lux) by setting
 * "high threshold windows setting" register.
 */
void ambient5_set_high_light_level_threshold ( ambient5_t* ctx,
	                                           float high_light_level_threshold );

/**
 * @brief Set high light level threshold.
 *
 * @param ctx                         Click object.
 *
 * @description This function powers device on and sets basic settings.
 */
void ambient5_power_on ( ambient5_t* ctx );

/**
 * @brief Checking INT pin state.
 *
 * @param ctx                         Click object.
 *
 * @returns INT pin state;            0-LOW, 1-HIGH.
 *
 * @description This function checks INT pin state.
 */
uint8_t ambient5_checkIntPin ( ambient5_t* ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AMBIENT5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

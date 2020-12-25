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
 * \brief This file contains API for Buck-Boost  Click driver.
 *
 * \addtogroup buckboost Buck-Boost  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCKBOOST_H
#define BUCKBOOST_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BUCKBOOST_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.vs2= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.run= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.vs3= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.pwm= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.vs1= MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCKBOOST_RETVAL  uint8_t

#define BUCKBOOST_OK           0x00
#define BUCKBOOST_INIT_ERROR   0xFF
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

    digital_out_t vs2;
    digital_out_t run;
    digital_out_t vs3;
    digital_out_t pwm;
    digital_out_t vs1;

} buckboost_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t vs2;
    pin_name_t run;
    pin_name_t vs3;
    pin_name_t pwm;
    pin_name_t vs1;

} buckboost_cfg_t;

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
void buckboost_cfg_setup ( buckboost_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buckboost Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCKBOOST_RETVAL buckboost_init ( buckboost_t *ctx, buckboost_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Buck-Boost  click.
 */
void buckboost_default_cfg ( buckboost_t *ctx );

/**
 * @brief Enable the converter function.
 *
 * @param ctx  Click object.
 *
 * @description This function enable the converter of LTC3129-1 on Buck Boost Click
 * by set RST ( RUN ) pin ( logic 1 ).
 */
void buckboost_enable ( buckboost_t *ctx );

/**
 * @brief Disable the converter function.
 *
 * @param ctx  Click object.
 *
 * @description This function disable the converter of LTC3129-1 on Buck Boost Click
 * by clear RST ( RUN ) pin ( logic 0 ).
 */
void buckboost_disable ( buckboost_t *ctx );

/**
 * @brief Set fixed frequency PWM operation function.
 *
 * @param ctx  Click object.
 *
 * @description This function set fixed frequency PWM operation mode
 * of LTC3129-1 on Buck Boost Click
 * by set PWM pin ( logic 1 ).
 */
void buckboost_set_mode_fixed_freq ( buckboost_t *ctx );

/**
 * @brief Enables automatic burst mode operation
 *
 * @param ctx  Click object.
 * 
 * @description This function enables automatic burst mode operation
 * of LTC3129-1 on Buck Boost Click
 * by clear PWM pin ( logic 0 ).
 */
void buckboost_enables_auto_burst_mode ( buckboost_t *ctx );

/**
 * @brief Set the output voltage of 2500 mV function
 *
 * @param ctx  Click object.
 * 
 * @description This function set the output voltage of 2500 mV function
 * of LTC3129-1 on Buck Boost Click
 * by :
 * - VS1 : clear INT pin ( logic 0 ),
 * - VS2 : clear AN  pin ( logic 0 ) and
 * - VS3 : clear CS  pin ( logic 0 ).
 */
void buckboost_set_2500mv ( buckboost_t *ctx );

/**
 * @brief Set the output voltage of 3000 mV function
 *
 * @param ctx  Click object.
 * 
 * @description This function set the output voltage of 3000 mV function
 * of LTC3129-1 on Buck Boost Click
 * by :
 * - VS1 : clear INT pin ( logic 0 ),
 * - VS2 : clear AN  pin ( logic 0 ) and
 * - VS3 : set   CS  pin ( logic 1 ).
 */
void buckboost_set_3300mv ( buckboost_t *ctx );

/**
 * @brief Set the output voltage of 4100 mV function
 *
 * @param ctx  Click object.
 * 
 * @description This function set the output voltage of 4100 mV function
 * of LTC3129-1 on Buck Boost Click
 * by :
 * - VS1 : clear INT pin ( logic 0 ),
 * - VS2 : set   AN  pin ( logic 1 ) and
 * - VS3 : clear CS  pin ( logic 0 ).
 */
void buckboost_set_4100mv ( buckboost_t *ctx );

/**
 * @brief Set the output voltage of 5000 mV function
 *
 * @param ctx  Click object.
 * 
 * @description This function set the output voltage of 5000 mV function
 * of LTC3129-1 on Buck Boost Click
 * by :
 * - VS1 : clear INT pin ( logic 0 ),
 * - VS2 : set   AN  pin ( logic 1 ) and
 * - VS3 : set   CS  pin ( logic 1 ).
 */
void buckboost_set_5000mv ( buckboost_t *ctx );

/**
 * @brief Set the output voltage of 6900 mV function
 *
 * @param ctx  Click object.
 * 
 * @description This function set the output voltage of 6900 mV function
 * of LTC3129-1 on Buck Boost Click
 * by :
 * - VS1 : set   INT pin ( logic 1 ),
 * - VS2 : clear AN  pin ( logic 0 ) and
 * - VS3 : clear CS  pin ( logic 0 ).
 */
void buckboost_set_6900mv ( buckboost_t *ctx );

/**
 * @brief Set the output voltage of 8200 mV function
 *
 * @param ctx  Click object.
 * 
 * @description This function set the output voltage of 8200 mV function
 * of LTC3129-1 on Buck Boost Click
 * by :
 * - VS1 : set   INT pin ( logic 1 ),
 * - VS2 : clear AN  pin ( logic 0 ) and
 * - VS3 : set   CS  pin ( logic 1 ).
 */
void buckboost_set_8200mv ( buckboost_t *ctx );

/**
 * @brief Set the output voltage of 12000 mV function
 *
 * @param ctx  Click object.
 * 
 * @description This function set the output voltage of 12000 mV function
 * of LTC3129-1 on Buck Boost Click
 * by :
 * - VS1 : set   INT pin ( logic 1 ),
 * - VS2 : set   AN  pin ( logic 1 ) and
 * - VS3 : clear CS  pin ( logic 0 ).
 */
void buckboost_set_12000mv ( buckboost_t *ctx );

/**
 * @brief Set the output voltage of 15000 mV function
 *
 * @param ctx  Click object.
 * 
 * @description This function set the output voltage of 15000 mV function
 * of LTC3129-1 on Buck Boost Click
 * by :
 * - VS1 : set   INT pin ( logic 1 ),
 * - VS2 : set   AN  pin ( logic 1 ) and
 * - VS3 : set   CS  pin ( logic 1 ).
 */
void buckboost_set_15000mv ( buckboost_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BUCKBOOST_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

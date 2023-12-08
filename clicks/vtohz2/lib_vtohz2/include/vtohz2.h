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
 * \brief This file contains API for V to Hz 2 Click driver.
 *
 * \addtogroup vtohz2 V to Hz 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef VTOHZ2_H
#define VTOHZ2_H

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
#include "drv_pwm.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define VTOHZ2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.fo = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define VTOHZ2_RETVAL  uint8_t

#define VTOHZ2_OK           0x00
#define VTOHZ2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup en_dis Enable/Disable
 * \{
 */
#define VTOHZ2_ENABLE     1
#define VTOHZ2_DISABLE    0
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define VTOHZ2_DEF_FREQ     20000
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

    digital_out_t en;

    // Input pins 

    digital_in_t fo;
    
    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint32_t  pwm_freq;

} vtohz2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t fo;

    // static variable 

    uint32_t  dev_pwm_freq;

} vtohz2_cfg_t;

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
void vtohz2_cfg_setup ( vtohz2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param vtohz2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
VTOHZ2_RETVAL vtohz2_init ( vtohz2_t *ctx, vtohz2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for VToHz2 click.
 */
void vtohz2_default_cfg ( vtohz2_t *ctx );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void vtohz2_set_duty_cycle ( vtohz2_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void vtohz2_pwm_stop ( vtohz2_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void vtohz2_pwm_start ( vtohz2_t *ctx );

/**
 * @brief Enable function
 *
 * @param ctx Click object.
 * 
 * @param state    <pre>
 *                   0 - Disable
 *                   1 - Enable
 *                 </pre>
 * 
 * @descripion Function performs enabling and disabling of the device.
 */
void vtohz2_enable ( vtohz2_t *ctx, uint8_t state );

/**
 * @brief Frequency Out Get function
 *
 * @param ctx Click object.
 * 
 * @returns State of the INT pin (out frequency)
 *
 * @description Function gets the out frequency on mikrobus INT pin.
 */
uint8_t vtohz2_get_freq_out ( vtohz2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _VTOHZ2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

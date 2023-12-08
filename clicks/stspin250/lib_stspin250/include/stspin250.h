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
 * \brief This file contains API for STSPIN250 Click driver.
 *
 * \addtogroup stspin250 STSPIN250 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef STSPIN250_H
#define STSPIN250_H

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
#define STSPIN250_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.ph = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define STSPIN250_RETVAL  uint8_t

#define STSPIN250_OK           0x00
#define STSPIN250_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup en_dis Enable/Disable
 * \{
 */
#define STSPIN250_DEVICE_ENABLE     1
#define STSPIN250_DEVICE_DISABLE    0
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define STSPIN250_DEF_FREQ     20000 //500
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

    digital_out_t ph;
    digital_out_t rst;
    digital_out_t en;

    // Input pins 

    digital_in_t flt;
    
    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint32_t pwm_freq;

} stspin250_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t ph;
    pin_name_t rst;
    pin_name_t en;
    pin_name_t flt;

    // static variable 

    uint32_t  dev_pwm_freq;

} stspin250_cfg_t;

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
void stspin250_cfg_setup ( stspin250_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
STSPIN250_RETVAL stspin250_init ( stspin250_t *ctx, stspin250_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Stspin250 click.
 */
void stspin250_default_cfg ( stspin250_t *ctx );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void stspin250_set_duty_cycle ( stspin250_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void stspin250_pwm_stop ( stspin250_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void stspin250_pwm_start ( stspin250_t *ctx );

/**
 * @brief Enable pin function.
 *
 * @param ctx     Click object.
 * @param state   Desired pin state.
 *
 * @description This function regulates enable pin state.
 */
void stspin250_enable ( stspin250_t *ctx, uint8_t state);

/**
 * @brief Dir ctrl pin function.
 *
 * @param ctx     Click object.
 * @param state   Desired pin state.
 *
 * @description This function regulates Direction control pin state. It controls direction 
 * of the current.
 */
void stspin250_set_ph ( stspin250_t *ctx, uint8_t state );

/**
 * @brief Reset pin function.
 *
 * @param ctx     Click object.
 * @param state   Desired pin state.
 *
 * @description This function regulates reset pin state.
 */
void stspin250_reset ( stspin250_t *ctx );

/**
 * @brief Fault get function.
 *
 * @param ctx     Click object.
 * @param state   Desired pin state.
 *
 * @description This function gets fault state from the flt pin.
 */
uint8_t stspin250_get_fault ( stspin250_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _STSPIN250_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

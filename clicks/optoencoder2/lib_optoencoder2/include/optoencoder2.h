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
 * \brief This file contains API for Opto Encoder 2 Click driver.
 *
 * \addtogroup optoencoder2 Opto Encoder 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OPTOENCODER2_H
#define OPTOENCODER2_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define OPTOENCODER2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.b_pin = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.a_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OPTOENCODER2_OK             0
#define OPTOENCODER2_ERROR         -1
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
    digital_in_t b_pin;
    digital_in_t a_pin;

    uint32_t timeout_counter;
    int32_t position_counter;

} optoencoder2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 
    pin_name_t b_pin;
    pin_name_t a_pin;

} optoencoder2_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void optoencoder2_cfg_setup ( optoencoder2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param optoencoder2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t optoencoder2_init ( optoencoder2_t *ctx, optoencoder2_cfg_t *cfg );

/**
 *
 * @brief Getting PWM pin state
 *
 * @param ctx  Click object.
 *
 * @returns 0 for PWM pin LOW state
 * @returns 1 for PWM pin HIGH state
 *
 * @details This function gets state of PWM pin
 */
uint8_t optoencoder2_pwm_get ( optoencoder2_t *ctx );

/**
 *
 * @brief Getting INT pin state
 *
 * @param ctx  Click object.
 *
 * @returns 0 for INT pin LOW state
 * @returns 1 for INT pin HIGH state
 *
 * @details This function gets state of INT pin 
 */
uint8_t optoencoder2_int_get ( optoencoder2_t *ctx );

/**
 *
 * @brief Getting encoder position
 *
 * @param ctx  Click object.
 *
 * @returns Current encoder position
 *
 * @details This function returns current encoder position 
 */
int32_t optoencoder2_get_position ( optoencoder2_t *ctx );

/**
 *
 * @brief Reset encoder counter
 *
 * @param ctx  Click object. 
 *
 * @details This function resets encoder counter to 0(zero)
 */
void optoencoder2_zero_counter ( optoencoder2_t *ctx );

/**
 *
 * @brief Incrementing/decrementing encoder counter
 *
 * @param n_cycles   Number of times(cycles) used to detect rising edge on channel A
 * @param ctx  Click object.
 * 
 * @note 
 * <pre>
 * This function - increments/decrements encoder position
 *               - checks for rising edge on Channel A (INT pin), within specified number of cycles (n_cycles), and increments or decrements encoder position
 *               - increments encoder position if Channel B (PWM pin) is in LOW state
 *               - decrements encoder position if Channel B (PWM pin) is in HIGH state
 *               - can be used to detect direction of rotation by comparing two consecutive encoder positions
 * </pre>
 *
 * @returns 0 if rising edge on channel A had been detected, within specified number of cycles (n_cycles)
 * @returns 1 if rising edge on channel A had not been detected, within specified number of cycles (n_cycles)
 */
uint8_t optoencoder2_isr ( optoencoder2_t *ctx, uint8_t n_cycles );

#ifdef __cplusplus
}
#endif
#endif  // _OPTOENCODER2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

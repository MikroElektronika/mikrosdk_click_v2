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
 * \brief This file contains API for ButtonR Click driver.
 *
 * \addtogroup buttonr ButtonR Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUTTONR_H
#define BUTTONR_H

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
#define BUTTONR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUTTONR_RETVAL  uint8_t

#define BUTTONR_OK           0x00
#define BUTTONR_INIT_ERROR   0xFF
/** \} */

#define T_BUTTONR_P    const uint8_t*

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
    digital_out_t pwm;

    // Input pins 

    digital_in_t int_pin;

} buttonr_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t pwm;
    pin_name_t int_pin;

} buttonr_cfg_t;

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
void buttonr_cfg_setup ( buttonr_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buttonr Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUTTONR_RETVAL buttonr_init ( buttonr_t *ctx, buttonr_cfg_t *cfg );


/**
 * @brief Detecting button press state function
 *
 *
 * @param ctx  Click object.
 *
 * @return State of INT pin:
 * 0 - button OFF;
 * 1 - button ON;
 *
 * @note
 * <pre>
 * Function detecting states when button is pressed
 * and returns the state of the INT pin.
 * INT pin can be configured to show are data registers updated
 * with the new values or not.
 * </pre>
 */
uint8_t buttonr_press_button( buttonr_t *ctx );

/**
 * @brief Turn on light on the button function
 *
 *
 * @param ctx  Click object.
 *
 * Function turn on light on the button
 * - set PWM pin high.
 */
void buttonr_turn_on_led( buttonr_t *ctx );

/**
 * @brief Turn off light on the button function
 *
 *
 * @param ctx  Click object.
 *
 * Function turn off light on the button
 * - set PWM pin low.
 */
void buttonr_turn_off_led( buttonr_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BUTTONR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
